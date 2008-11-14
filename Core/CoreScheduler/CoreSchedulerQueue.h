#ifndef CORESCHEDULERQUEUE_H
#define CORESCHEDULERQUEUE_H

#include "../CoreBasicTypeDefine.h"
#include "CoreScheduler.config"
#include "../CoreMemory/CoreMemory.h"

struct CoreScheduler_QueueItem{
	struct CoreScheduler_QueueItem* previous;
	struct CoreScheduler_QueueItem* next;
	CoreScheduler_JobID				id;
};

typedef struct CoreScheduler_QueueItem CoreScheduler_QueueItem;
typedef struct CoreScheduler_QueueItem *CoreScheduler_QueueItemRef;

CoreScheduler_QueueItemRef	CoreScheduler_HeadJob;
CoreScheduler_QueueItemRef	CoreScheduler_FootJob;
Data_4Byte					CoreScheduler_CurrentJobQuantity;

void				CoreScheduler_QueueInit(void);
void				CoreScheduler_QueueEmpty(void);
Data_Boolean		CoreScheduler_QueuePush(CoreScheduler_JobID id);
CoreScheduler_JobID	CoreScheduler_QueuePop(Data_Boolean *hasItem);

#endif
