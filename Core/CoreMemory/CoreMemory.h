#ifndef COREMEMORY_H
#define	COREMEMORY_H

#include <stdlib.h>
//Must Fix It!!!

#include "../../SystemInformation.h"
#include "../CoreBasicTypeDefine.h"
#include "CoreMemory.config"

void*	CoreMemory_Alloc(CoreMemorySize size);
void	CoreMemory_Free(void *point);

//void*	CoreMemory_AllocInStack(CoreMemorySize size)
#if defined(SystemInformation_AVR)
	#define CoreMemory_AllocInStack(SIZE) alloca(sizeof(Data_1Byte) * SIZE);
#endif

#endif
