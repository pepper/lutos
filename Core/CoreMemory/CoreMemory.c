#include "CoreMemory.h"

Data_1Byte *CoreMemory_PhysicalMemorySpace;

void CoreMemory_Init(void){
	//Init Hardware
	Porting_ExternalMemoryInit();
	//Alloc All External Memory
	CoreMemory_PhysicalMemorySpace = (Data_1Byte*)malloc(sizeof(Data_1Byte) * CoreMemory_ExternalMemorySize);
}

Data_Boolean CoreMemory_MemorySpaceVerify(void){
	Data_4Byte i;
	Data_1Byte j;
	for(i = 0, j = (Data_1Byte)CoreMemory_ExternalMemorySize; i < CoreMemory_ExternalMemorySize; i++, j++){
		CoreMemory_PhysicalMemorySpace[i] = (Data_1Byte)j;
	}
	for(i = 0, j = (Data_1Byte)CoreMemory_ExternalMemorySize; i < CoreMemory_ExternalMemorySize; i++, j++){
		if(CoreMemory_PhysicalMemorySpace[i] != (Data_1Byte)j){
			return FALSE;
		}
	}
	return TRUE;
}

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
