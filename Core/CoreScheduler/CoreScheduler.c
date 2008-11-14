#include "CoreScheduler.h"

void CoreScheduler_Init(void){
	CoreScheduler_QueueInit();
	CoreScheduler_PauseState = 0xFF;
	CoreScheduler_JobAllowRetrigMask = 0xFF;
	Data_1Byte i;
	for(i = 0; i < 4; i++ ){
		CoreScheduler_JobTrigTimes[i] = 0;
	}
}

void CoreScheduler_RegisterJob(CoreScheduler_JobID id, void (*function)(void)){
	CoreScheduler_JobExecuteFunction[id] = function;
}

void CoreScheduler_NeedToWork(CoreScheduler_JobID id){
	CoreScheduler_JobStatus |= (((CoreScheduler_JobStatus & (1 << id)) == 0)? (1 << id):(1 << (id + 4)) );
	CoreScheduler_JobTrigTimes[id]++;
}

void CoreScheduler_AllowRetrigger(CoreScheduler_JobID id, Data_Boolean enable){
	if(enable == TRUE){
		SetBit(CoreScheduler_JobAllowRetrigMask, (id + 4));
	}
	else{
		ClearBit(CoreScheduler_JobAllowRetrigMask, (id + 4));
	}
}

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
	//AVR interrupt ois triggered by set the interrupt flag, so that event occur during Disable Interrupt time will trig after Enable Interrupt
	//For other CPU make sure to check this point!!!
	Data_1Byte JobStatus = CoreScheduler_JobStatus;	
	CoreScheduler_JobStatus = 0;
	sei();	//Enable Interrupt After 4 CPU Clock

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
}

//void	CoreScheduler_Pause(Data_1Byte type);
//void	CoreScheduler_Reset(Data_1Byte type);

