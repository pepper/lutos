#ifndef COREMEMORY_H
#define	COREMEMORY_H

#include "../../SystemInformation.h"
#include "CoreMemory.config"
#include "../CoreScheduler/CoreScheduler.h"

#define	CoreMemory_SpaceTypeFIFO			0
#define	CoreMemory_SpaceTypeCircularBuffer	1
#define	CoreMemory_SpaceTypeStack			2
#define	CoreMemory_SpaceTypeCustomType		3

#define	CoreMemory_EventHandlerTypeEmpty	0
#define	CoreMemory_EventHandlerTypeFull		1
#define	CoreMemory_EventHandlerTypeCross	2

struct CoreMemory_SpaceMarker{
	Data_1Byte			type;
	Data_Boolean		used;
	Data_Boolean		lock;
	CoreMemory_Size		startAddress;
	CoreMemory_Size		endAddress;
	CoreMemory_Size		size;
	Data_1Byte			elementSize;
	CoreMemory_Size		startPoint;
	CoreMemory_Size		endPoint;
	CoreMemory_Size		usedSize;
	CoreScheduler_JobID	eventJob[3];
};
typedef struct CoreMemory_SpaceMarker CoreMemory_Space;

void				CoreMemory_Init(void);
Data_Boolean		CoreMemory_MemorySpaceVerify(void);
Data_Boolean		CoreMemory_Defrag(void);
Data_Boolean		CoreMemory_DropMemory(void);
CoreMemory_Space*	CoreMemory_CreateSpace(Data_1Byte type, CoreMemory_Size size, Data_1Byte elementSize);
Data_Boolean		CoreMemory_DeleteSpace(CoreMemory_Space* space);
Data_Boolean		CoreMemory_DropSpace(CoreMemory_Space* space);
Data_Boolean		CoreMemory_Push(CoreMemory_Space* space, CoreMemory_Size index, void *data);
Data_Boolean		CoreMemory_Pop(CoreMemory_Space* space, CoreMemory_Size index,void *data);
void				CoreMemory_SetInterrupt(CoreMemory_Space* space, Data_1Byte interruptType, CoreScheduler_JobID jobId);

#endif
