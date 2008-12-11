#include "CoreScheduler.h"

INLINE void CoreScheduler_CheckAndPushLeaf(Data_1Byte);

//Check!!!
void CoreScheduler_Init(void){
	Data_1Byte i, j;
	
	//Initialize Core Scheduler State
	CoreScheduler_QueueInit();
	CoreScheduler_CurrentCollectBuffer = 0;
	
	//Initialize Job Tree Leaf State
	for (i = 0; i < CoreScheduler_JobTreeLeafQuantity; i++ ){
#if defined(CoreScheduler_EnableCheckRetrig)
		CoreScheduler_JobTreeLeaf[i].jobAllowRetrigMask = 0xFF;
#endif
		for (j = 0; j < 2; j++ ) {
			CoreScheduler_JobTreeLeaf[i].jobStatus[j] = 0;
			CoreScheduler_RegisterJob(i, CoreScheduler_NothingToDo);
#if defined(CoreScheduler_EnableCheckRetrig)
			Data_1Byte k;
			for(k = 0; k < 4; k++ ){
				CoreScheduler_JobTreeLeaf[i].jobTrigTimes[k][j] = 0;				
			}
#endif
		}
	}
	//Construct & Initialize Job Tree Node
	for(i = 0; i < 2; i++ ){
#if CoreScheduler_Level > 1
		CoreScheduler_JobTreeNodeLevel1.childStatus[i] = 0;
#endif
#if CoreScheduler_Level > 2
		for(j = 0; j < 8; j++){
			CoreScheduler_JobTreeNodeLevel2[j].childStatus[i] = 0;
		}
#endif
	}
}

//Check!!!
//To Be Fix: Only Support Level<=4 Now
void CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void)){
	CoreScheduler_JobTreeLeaf[id >> 2].jobExecuteFunction[id & 0x03] = function;
}

//Check!!!
void CoreScheduler_NeedToWork(CoreScheduler_JobID id){
#if defined(CoreScheduler_EnableCheckRetrig)
	CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] |= (((CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] & (1 << (id & 0x03))) == 0)? (1 << (id & 0x03)):(1 << ((id & 0x03) + 4)));
	CoreScheduler_JobTreeLeaf[id >> 2].jobTrigTimes[id & 0x03][CoreScheduler_CurrentCollectBuffer]++;
#else
	CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << (id & 0x03));
#endif

//Set parent node
#if CoreScheduler_Level > 1
	id = id >> 2;
#endif
#if CoreScheduler_Level > 2
	CoreScheduler_JobTreeNodeLevel2[id >> 3].childStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << (id & 0x07));
	id = id >> 3;
#endif
#if CoreScheduler_Level > 1
	CoreScheduler_JobTreeNodeLevel1.childStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << id);
#endif
}

//Check!!!
#if defined(CoreScheduler_EnableCheckRetrig)
void CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable){
	if(enable == TRUE){
		SetBit(CoreScheduler_JobTreeLeaf[id >> 2].jobAllowRetrigMask, ((id & 0x03) + 4));
	}
	else{
		ClearBit(CoreScheduler_JobTreeLeaf[id >> 2].jobAllowRetrigMask, ((id & 0x03) + 4));
	}
}
#endif

//Check!!!
//STILL NOT FINISHED !!!
void CoreScheduler_RunLoop(void){
	while(1){
		//Using to pause
#if defined(CoreScheduler_EnablePauseExecuteJob)
		while(CoreScheduler_PauseExecuteJobState == FALSE){
#endif
			CoreScheduler_CheckAndPush();
			CoreScheduler_Execute();
#if defined(CoreScheduler_EnablePauseExecuteJob)
		}
#endif
	}
}

//Check!!!
void CoreScheduler_Execute(void){
	Data_Boolean hasItem;
	void (*executeFunction)(void) = CoreScheduler_QueuePop(&hasItem);
	if(hasItem == TRUE){
		executeFunction();
	}
}

INLINE void CoreScheduler_CheckAndPushLeaf(Data_1Byte jobTreeLeafIndex){
	Data_1Byte j;
	Data_1Byte jobStatusLeaf = CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobStatus[CoreScheduler_CurrentCheckBuffer];
	Data_1Byte jobStatusLeafStart = pgm_read_byte(&(CoreScheduler_JobLookUpTableLeafStart[jobStatusLeaf & 0x0F]));
	Data_1Byte jobStatusLeafEnd = jobStatusLeafStart + pgm_read_byte(&(CoreScheduler_JobLookUpTableLeafNumber[jobStatusLeaf & 0x0F]));
#if defined(CoreScheduler_EnableCheckRetrig)
	Data_2Byte k;
	jobStatusLeaf &= CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobAllowRetrigMask;
	for(j = jobStatusLeafStart; j < jobStatusLeafEnd; j++){
		if((0x10 << pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))) & jobStatusLeaf){
			for(k = 0; k < CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobTrigTimes[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))][CoreScheduler_CurrentCheckBuffer]; k++ ){
				CoreScheduler_QueuePush(CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobExecuteFunction[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))]);
			}
		}
		else{
			CoreScheduler_QueuePush(CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobExecuteFunction[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))]);
		}
		CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobTrigTimes[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))][CoreScheduler_CurrentCheckBuffer] = 0;
	}
#else //For defined(CoreScheduler_EnableCheckRetrig)
	for(j = jobStatusLeafStart; j < jobStatusLeafEnd; j++){
		CoreScheduler_QueuePush(CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobExecuteFunction[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationLeaf[j]))]);
	}
#endif //For defined(CoreScheduler_EnableCheckRetrig)
	CoreScheduler_JobTreeLeaf[jobTreeLeafIndex].jobStatus[CoreScheduler_CurrentCheckBuffer] = 0;
}

//STILL NOT FINISHED !!!
void CoreScheduler_CheckAndPush(void){
#if defined(CoreScheduler_EnablePausePushJob)
	if(CoreScheduler_PausePushJobState){
		return;
	}
#endif
	CoreScheduler_CurrentCheckBuffer = CoreScheduler_CurrentCollectBuffer;
	
	cli();	//Disable Interrupt
	//AVR interrupt triggered by set the interrupt flag, so that event occur during Disable Interrupt time will trig after Enable Interrupt
	//For other CPU make sure to check this point !!!
	CoreScheduler_CurrentCollectBuffer = (CoreScheduler_CurrentCollectBuffer + 1) & 0x01;
	sei();	//Enable Interrupt After 4 CPU Clock
	
#if CoreScheduler_Level > 1
	Data_2Byte i;
	Data_1Byte jobStatusNode = CoreScheduler_JobTreeNodeLevel1.childStatus[CoreScheduler_CurrentCheckBuffer];
	Data_2Byte jobStatusLevel1Start = pgm_read_dword(&(CoreScheduler_JobLookUpTableNodeStart[jobStatusNode]));
	Data_2Byte jobStatusLevel1End = jobStatusLevel1Start + pgm_read_byte(&(CoreScheduler_JobLookUpTableNodeNumber[jobStatusNode]));
	for(i = jobStatusLevel1Start; i < jobStatusLevel1End; i++ ){
#if CoreScheduler_Level > 2
		Data_2Byte j;
		Data_1Byte jobStatusNode = CoreScheduler_JobTreeNodeLevel2[i].childStatus[CoreScheduler_CurrentCheckBuffer];
		Data_2Byte jobStatusLevel2Start = pgm_read_dword(&(CoreScheduler_JobLookUpTableNodeStart[jobStatusNode]));
		Data_2Byte jobStatusLevel2End = jobStatusLevel2Start + pgm_read_byte(&(CoreScheduler_JobLookUpTableNodeNumber[jobStatusNode]));
		Data_1Byte baseNode = i << 3;
		for(j = jobStatusLevel2Start; j < jobStatusLevel2End; j++ ){
			CoreScheduler_CheckAndPushLeaf((pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationNode[j]))) + baseNode);
		}
		CoreScheduler_JobTreeNodeLevel2[i].childStatus[CoreScheduler_CurrentCheckBuffer] = 0;
#else
		CoreScheduler_CheckAndPushLeaf(pgm_read_byte(&(CoreScheduler_JobPermutationAndCombinationNode[i])));
#endif
	}
	CoreScheduler_JobTreeNodeLevel1.childStatus[CoreScheduler_CurrentCheckBuffer] = 0;
#else //For CoreScheduler_Level > 1
	CoreScheduler_CheckAndPushLeaf(0);
#endif //For CoreScheduler_Level > 1
}

//void	CoreScheduler_Pause(Data_1Byte type);
void CoreScheduler_Reset(Data_1Byte type){
	switch(type){
		case CoreScheduler_QueueResetType:
			CoreScheduler_QueueEmpty();
			break;
		
		case CoreScheduler_JobsResetType:
			CoreScheduler_Init();
			break;
	}
}

void CoreScheduler_NothingToDo(void){
//Report an ERROE occur!!!
}
