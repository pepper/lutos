#include "CoreScheduler.h"

void CoreScheduler_Init(void){
	Data_2Byte i, j;
	//Initialize Core Scheduler State
	CoreScheduler_QueueInit();
	CoreScheduler_CurrentCollectBuffer = 0;
	
	//Initialize Job Tree Leaf State
	for (i = 0; i < CoreScheduler_JobCapability; i++ ){
#if defined(CoreScheduler_CheckRetrig)
		CoreScheduler_JobTreeLeaf[i].jobAllowRetrigMask = 0xFF;
#endif
		for (j = 0; j < 2; j++ ) {
			CoreScheduler_JobTreeLeaf[i].jobStatus[j] = 0;
			CoreScheduler_RegisterJob(i, CoreScheduler_NothingToDo);

#if defined(CoreScheduler_CheckRetrig)
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
		CoreScheduler_JobTreeNode[0] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 1);
		CoreScheduler_JobTreeNode[0][0].childStatus[i] = 0;
#endif
#if CoreScheduler_Level > 2
		CoreScheduler_JobTreeNode[1] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 4);
		for(j = 0; j < 4; j++){
			CoreScheduler_JobTreeNode[1][j].childStatus[i] = 0;
		}
#endif
#if CoreScheduler_Level > 3
		CoreScheduler_JobTreeNode[2] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 16);
		for(j = 0; j < 16; j++){
			CoreScheduler_JobTreeNode[2][j].childStatus[i] = 0;
		}
#endif
	}
}

//To Be Fix: Only Support Level<=4 Now
void CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void)){
	CoreScheduler_JobTreeLeaf[id >> 2].jobExecuteFunction[id & 0x03] = function;
}

void CoreScheduler_NeedToWork(CoreScheduler_JobID id){
	CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << (id & 0x03));
#if defined(CoreScheduler_CheckRetrig)
//STILL NOT FINISHED !!!
	CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] |= (((CoreScheduler_JobTreeLeaf[id >> 2].jobStatus[CoreScheduler_CurrentCollectBuffer] & (1 << (id & 0x03))) == 0)? (1 << (id & 0x03)):(1 << ((id & 0x03) + 4)));
	CoreScheduler_JobTreeLeaf[id >> 2].jobTrigTimes[id & 0x03][CoreScheduler_CurrentCollectBuffer]++;
#endif

//Set parent node
	id = id >> 2;
#if CoreScheduler_Level > 3
	CoreScheduler_JobTreeNode[2][id >> 2].childStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << (id & 0x03));
	id = id >> 2;
#endif
#if CoreScheduler_Level > 2
	CoreScheduler_JobTreeNode[1][id >> 2].childStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << (id & 0x03));
	id = id >> 2;
#endif
#if CoreScheduler_Level > 1
	CoreScheduler_JobTreeNode[0][0].childStatus[CoreScheduler_CurrentCollectBuffer] |= (1 << id);
#endif
}

#if defined(CoreScheduler_CheckRetrig)
void CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable){
	if(enable == TRUE){
		SetBit(CoreScheduler_JobTreeLeaf[id >> 2].jobAllowRetrigMask, ((id & 0x03) + 4));
	}
	else{
		ClearBit(CoreScheduler_JobTreeLeaf[id >> 2].jobAllowRetrigMask, ((id & 0x03) + 4));
	}
}
#endif

//STILL NOT FINISHED !!!
void CoreScheduler_RunLoop(void){
	while(1){
		//Using to pause
		while(1){
			CoreScheduler_CheckAndPush();
			CoreScheduler_Execute();
		}
	}
}

void CoreScheduler_Execute(void){
	Data_Boolean hasItem;
	CoreScheduler_JobID id = CoreScheduler_QueuePop(&hasItem);
	if(hasItem == TRUE){
		CoreScheduler_JobTreeLeaf[id >> 2].jobExecuteFunction[id & 0x03]();
	}
}

//STILL NOT FINISHED !!!
void CoreScheduler_CheckAndPush(void){
	Data_1Byte i;
	Data_1Byte CoreScheduler_CurrentCheckBuffer = CoreScheduler_CurrentCollectBuffer;
	
	cli();	//Disable Interrupt
	//AVR interrupt triggered by set the interrupt flag, so that event occur during Disable Interrupt time will trig after Enable Interrupt
	//For other CPU make sure to check this point !!!
	CoreScheduler_CurrentCollectBuffer = (CoreScheduler_CurrentCollectBuffer + 1) & 0x01;
	sei();	//Enable Interrupt After 4 CPU Clock
	
#if CoreScheduler_Level > 1
	
#else
	Data_1Byte JobStatus = CoreScheduler_JobTreeLeaf[0].jobStatus[CoreScheduler_CurrentCheckBuffer];
	Data_1Byte start = pgm_read_dword(&(CoreScheduler_JobLookUpTableStart[JobStatus & 0x0F]));
	Data_1Byte end = start + pgm_read_byte(&(CoreScheduler_JobLookUpTableNumber[JobStatus & 0x0F]));
#if defined(CoreScheduler_CheckRetrig)
	Data_2Byte j;
	JobStatus &= CoreScheduler_JobTreeLeaf[0].jobAllowRetrigMask;
	for(i = start; i < end; i++){
		if((0x10 << pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i]))) & JobStatus){
			for(j = 0; j < CoreScheduler_JobTreeLeaf[0].jobTrigTimes[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i]))][CoreScheduler_CurrentCheckBuffer]; j++ ){
				CoreScheduler_QueuePush(pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i])));
			}
		}
		else{
			CoreScheduler_QueuePush(pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i])));
		}
		CoreScheduler_JobTreeLeaf[0].jobTrigTimes[pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i]))][CoreScheduler_CurrentCheckBuffer] = 0;
	}
#else
	for(i = start; i < end; i++){
		CoreScheduler_QueuePush(pgm_read_byte(&(CoreScheduler_JobPermutationAndCombination[i])));
	}
#endif
	CoreScheduler_JobTreeLeaf[0].jobStatus[CoreScheduler_CurrentCheckBuffer] = 0;
#endif

}

//void	CoreScheduler_Pause(Data_1Byte type);
//void	CoreScheduler_Reset(Data_1Byte type);

void CoreScheduler_NothingToDo(void){
	
}
