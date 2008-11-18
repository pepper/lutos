#include "CoreScheduler.h"

void CoreScheduler_Init(void){
	Data_1Byte i, j;
	//Initialize Core Scheduler State
	CoreScheduler_QueueInit();
	CoreScheduler_CurrentCollectBuffer = 0;
	
	//Initialize Job Tree Leaf State
	for (i = 0; i < 2; i++ ){
		for (j = 0; j < CoreScheduler_JobCapability; j++ ) {
			CoreScheduler_JobTreeLeaf[i][j].jobStatus = 0;
			CoreScheduler_RegisterJob(i, CoreScheduler_NothingToDo);

#if defined(CoreScheduler_CheckRetrig)
			CoreScheduler_JobTreeLeaf[i][j].jobAllowRetrigMask = 0xFF;
			CoreScheduler_JobTreeLeaf[i][j].jobTrigTimes[0] = 0;
			CoreScheduler_JobTreeLeaf[i][j].jobTrigTimes[1] = 0;
			CoreScheduler_JobTreeLeaf[i][j].jobTrigTimes[2] = 0;
			CoreScheduler_JobTreeLeaf[i][j].jobTrigTimes[3] = 0;
#endif			

		}
	}
	
	//Construct & Initialize Job Tree Node
	for(i = 0; i < 2; i++ ){
#if CoreScheduler_Level > 1
		CoreScheduler_JobTreeNode[i][0] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 1);
		CoreScheduler_JobTreeNode[i][0][0] = 0;
#endif
#if CoreScheduler_Level > 2
		CoreScheduler_JobTreeNode[i][1] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 4);
		for(j = 0; j < 4; j++){
			CoreScheduler_JobTreeNode[i][1][j] = 0;
		}
#endif
#if CoreScheduler_Level > 3
		CoreScheduler_JobTreeNode[i][2] = CoreMemory_Alloc(sizeof(CoreScheduler_JobTreeNodeType) * 16);
		for(j = 0; j < 16; j++){
			CoreScheduler_JobTreeNode[i][2][j] = 0;
		}
#endif
	}
}

//To Be Fix: Only Support Level<=4 Now
void CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void)){
	CoreScheduler_JobTreeLeaf[CoreScheduler_CurrentCollectBuffer][id >> 2].jobExecuteFunction[id & 0xFC] = function;
}

void CoreScheduler_NeedToWork(CoreScheduler_JobID id){
	CoreScheduler_JobTreeLeaf[CoreScheduler_CurrentCollectBuffer][id >> 2].jobStatus |= (1 << id);
#if defined(CoreScheduler_CheckRetrig)
//STILL NOT FINISHED !!!
	//CoreScheduler_JobStatus |= (((CoreScheduler_JobStatus & (1 << id)) == 0)? (1 << id):(1 << (id + 4)) );
	//CoreScheduler_JobTrigTimes[id]++;
#endif
}

#if defined(CoreScheduler_CheckRetrig)
//STILL NOT FINISHED !!!
void CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable){
	if(enable == TRUE){
		SetBit(CoreScheduler_JobAllowRetrigMask, (id + 4));
	}
	else{
		ClearBit(CoreScheduler_JobAllowRetrigMask, (id + 4));
	}
}
#endif

void CoreScheduler_RunLoop(void){
	while(1){
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
		CoreScheduler_JobExecuteFunction[id]();
	}
}

void CoreScheduler_CheckAndPush(void){
	
	cli();	//Disable Interrupt
	//AVR interrupt triggered by set the interrupt flag, so that event occur during Disable Interrupt time will trig after Enable Interrupt
	//For other CPU make sure to check this point !!!
	CoreScheduler_CurrentCollectBuffer = (CoreScheduler_CurrentCollectBuffer + 1) % 2;
	sei();	//Enable Interrupt After 4 CPU Clock

	Data_1Byte JobStatus = CoreScheduler_JobStatus;	
	CoreScheduler_JobStatus = 0;
	
	JobStatus &= CoreScheduler_JobAllowRetrigMask;
	Data_1Byte start = CoreScheduler_JobLookUpTable[JobStatus & 0x0F].start;
	Data_1Byte end = start + CoreScheduler_JobLookUpTable[JobStatus & 0x0F].number;
	
	Data_1Byte i;
	for(i = start; i < end; i++){
		if((0x10 << CoreScheduler_JobPermutationAndCombination[i]) & JobStatus){
			Data_1Byte j;
			for(j = 0; j < CoreScheduler_JobTrigTimes[CoreScheduler_JobPermutationAndCombination[i]]; j++ ){
				CoreScheduler_QueuePush(CoreScheduler_JobPermutationAndCombination[i]);
			}
		}
		else{
			CoreScheduler_QueuePush(CoreScheduler_JobPermutationAndCombination[i]);
		}
		CoreScheduler_JobTrigTimes[i] = 0;
	}
	
	//Be sure to Zero CoreScheduler_JobStatus
}

//void	CoreScheduler_Pause(Data_1Byte type);
//void	CoreScheduler_Reset(Data_1Byte type);

void CoreScheduler_NothingToDo(void){
	
}
