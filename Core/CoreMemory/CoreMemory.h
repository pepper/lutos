#ifndef COREMEMORY_H
#define	COREMEMORY_H

#include <stdlib.h>
//Must Fix It!!!

#include "../../SystemInformation.h"
#include "../../Driver/Uart/Uart.h"
#include "CoreMemory.config"

#include "../CoreScheduler/CoreScheduler.h"

void*	CoreMemory_Alloc(CoreMemory_Size size);
void	CoreMemory_Free(void *point);

//void*	CoreMemory_AllocInStack(CoreMemorySize size)
#if defined(SystemInformation_AVR)
#	define CoreMemory_AllocInStack(SIZE) alloca(sizeof(Data_1Byte) * SIZE);
#endif

void						CoreMemory_Init(void);
Data_Boolean				CoreMemory_MemorySpaceVerify(void);
void						CoreMemory_Defrag(void);
CoreMemory_StorageSpaceID	CoreMemory_CreateSpace(Data_1Byte type, CoreMemory_Size size, Data_1Byte elementSize);
Data_Boolean				CoreMemory_DropSpace(CoreMemory_StorageSpaceID spaceID);
Data_Boolean				CoreMemory_DeleteSpace(CoreMemory_StorageSpaceID spaceID);
Data_Boolean				CoreMemory_Push(CoreMemory_StorageSpaceID spaceID, CoreMemory_Size index, void *data);
void						CoreMemory_Pop(CoreMemory_StorageSpaceID spaceID, CoreMemory_Size index,void *data);
void						CoreMemory_Interrupt(CoreMemory_StorageSpaceID spaceID, Data_1Byte interruptType, CoreScheduler_JobID jobId);
#endif
