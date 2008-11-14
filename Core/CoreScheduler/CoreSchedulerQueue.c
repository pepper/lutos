#include "CoreSchedulerQueue.h"

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

Data_Boolean CoreScheduler_QueuePush(CoreScheduler_JobID id){
	if(CoreScheduler_CurrentJobQuantity < CoreScheduler_MaximumQueueItemQuantrty){
		CoreScheduler_QueueItemRef newJob = CoreMemory_Alloc(sizeof(CoreScheduler_QueueItem));
		newJob->id = id;
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

CoreScheduler_JobID CoreScheduler_QueuePop(Data_Boolean *hasItem){
	*hasItem = TRUE;
	if(CoreScheduler_HeadJob != NULL){
		CoreScheduler_QueueItemRef deleteJob = CoreScheduler_HeadJob;
		CoreScheduler_JobID resultId = deleteJob->id;
		CoreScheduler_HeadJob = CoreScheduler_HeadJob->next;
		if(CoreScheduler_HeadJob != NULL){
			CoreScheduler_HeadJob->previous = NULL;
		}
		else{
			CoreScheduler_FootJob = NULL;
		}
		CoreScheduler_CurrentJobQuantity--;
		CoreMemory_Free(deleteJob);
		return resultId;
	}
	*hasItem = FALSE;
	return (CoreScheduler_JobID)NULL;
}
