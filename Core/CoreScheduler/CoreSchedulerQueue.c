#include "CoreSchedulerQueue.h"

CoreScheduler_QueueItemRef	CoreScheduler_HeadJob;
CoreScheduler_QueueItemRef	CoreScheduler_FootJob;
Data_4Byte					CoreScheduler_CurrentJobQuantity;

void CoreScheduler_QueueInit(void){
	CoreScheduler_QueueEmpty();
	CoreScheduler_HeadJob = NULL;
	CoreScheduler_FootJob = NULL;
	CoreScheduler_CurrentJobQuantity = 0;
}

void CoreScheduler_QueueEmpty(void){
	while(CoreScheduler_HeadJob != NULL){
		Data_Boolean hasItem;
		CoreScheduler_QueuePop(&hasItem);
	}
}

Data_Boolean CoreScheduler_QueuePush(void (*job)(void)){
	if(CoreScheduler_CurrentJobQuantity < CoreScheduler_MaximumQueueItemQuantrty){
		CoreScheduler_QueueItemRef newJob = malloc(sizeof(CoreScheduler_QueueItem));
		newJob->job = job;
		if(CoreScheduler_FootJob != NULL){
			CoreScheduler_FootJob->next = newJob;
			newJob->previous = CoreScheduler_FootJob;
			newJob->next = NULL;
			CoreScheduler_FootJob = newJob;
		}
		else if(CoreScheduler_HeadJob == NULL){
			CoreScheduler_HeadJob = newJob;
			CoreScheduler_HeadJob->next = NULL;
			CoreScheduler_HeadJob->previous = NULL;
			CoreScheduler_FootJob = CoreScheduler_HeadJob;
		}
		CoreScheduler_CurrentJobQuantity++;
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void (*CoreScheduler_QueuePop(Data_Boolean *hasItem))(void){
	*hasItem = TRUE;
	if(CoreScheduler_HeadJob != NULL){
		CoreScheduler_QueueItemRef deleteJob = CoreScheduler_HeadJob;
		void (*resultJob)(void) = deleteJob->job;
		CoreScheduler_HeadJob = CoreScheduler_HeadJob->next;
		if(CoreScheduler_HeadJob != NULL){
			CoreScheduler_HeadJob->previous = NULL;
		}
		else{
			CoreScheduler_FootJob = NULL;
		}
		CoreScheduler_CurrentJobQuantity--;
		free(deleteJob);
		return resultJob;
	}
	*hasItem = FALSE;
	return NULL;
}
