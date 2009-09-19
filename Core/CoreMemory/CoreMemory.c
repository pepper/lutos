#include "CoreMemory.h"

void* CoreMemory_Alloc(CoreMemory_Size size){
#if defined(SystemInformation_AVR)
	//#To Be Fix: This is a VARY SLOW way to get memory space.
	return malloc(sizeof(Data_1Byte) * size);
#endif
}

void CoreMemory_Free(void *point){
#if defined(SystemInformation_AVR)
	//#To Be Fix: This is a VARY SLOW way to get memory space.
	free(point);
#endif
}
