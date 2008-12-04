#ifndef CORESCHEDULERQUEUE_H
#define CORESCHEDULERQUEUE_H

#include "../CoreBasicTypeDefine.h"
#include "CoreScheduler.config"
#include "../CoreMemory/CoreMemory.h"

struct CoreScheduler_QueueItem{
	struct CoreScheduler_QueueItem* previous;
	struct CoreScheduler_QueueItem* next;
	void							(*job)(void);
};

typedef struct CoreScheduler_QueueItem CoreScheduler_QueueItem;
typedef struct CoreScheduler_QueueItem *CoreScheduler_QueueItemRef;

//To Be Fix: Add a preconstruct Quese Box(DO NOT USE ALLOC FUNCTION !!!)

CoreScheduler_QueueItemRef	CoreScheduler_HeadJob;
CoreScheduler_QueueItemRef	CoreScheduler_FootJob;
Data_4Byte					CoreScheduler_CurrentJobQuantity;

void			CoreScheduler_QueueInit(void);
void			CoreScheduler_QueueEmpty(void);
Data_Boolean	CoreScheduler_QueuePush(void (*job)(void));
void			(*CoreScheduler_QueuePop(Data_Boolean *hasItem))(void);

#endif
