#include "CoreMemory.h"

Data_1Byte*			CoreMemory_PhysicalMemorySpace;
CoreMemory_Size		CoreMemory_PhysicalMemoryUsedByte;
Data_1Byte			CoreMemory_SpaceCurrentQuantity;
CoreMemory_Space	CoreMemory_SpaceList[CoreMemory_SpaceQuantity];

void CoreMemory_Init(void){
	//Init Hardware
	Porting_ExternalMemoryInit();
	//Alloc All External Memory
	CoreMemory_PhysicalMemorySpace = (Data_1Byte*)malloc(sizeof(Data_1Byte) * CoreMemory_ExternalMemorySize);
	CoreMemory_PhysicalMemoryUsedByte = 0;
	CoreMemory_SpaceCurrentQuantity = 0;
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

Data_Boolean CoreMemory_Defrag(void){
	Data_Boolean needMove;
	Data_1Byte i, j, newSpaceQuantity;
	CoreMemory_Size spacing, newPhysicalMemoryUsedByte, k;
	for(i = 0; i < CoreMemory_SpaceCurrentQuantity; i++){
		if(CoreMemory_SpaceList[i].lock == FALSE || CoreMemory_SpaceList[i].used == FALSE){
			CoreMemory_SpaceList[i].lock = TRUE;
		}
		else{
			for(j = i - 1; ; j--){
				CoreMemory_SpaceList[j].lock = FALSE;
				if(j == 0){
					break;
				}
			}
			return FALSE;
		}
	}
	for(i = 0, newSpaceQuantity = 0, newPhysicalMemoryUsedByte = 0, needMove = FALSE, spacing = 0; i < CoreMemory_SpaceCurrentQuantity; i++){
		if(CoreMemory_SpaceList[i].used == TRUE){
			if(needMove == TRUE){
				CoreMemory_SpaceList[newSpaceQuantity] = CoreMemory_SpaceList[i];
				CoreMemory_SpaceList[newSpaceQuantity].startAddress -= spacing;
				CoreMemory_SpaceList[i].used = FALSE;
				for(k = 0; k < CoreMemory_SpaceList[newSpaceQuantity].size; k++){
					CoreMemory_PhysicalMemorySpace[CoreMemory_SpaceList[newSpaceQuantity].startAddress + k] = CoreMemory_PhysicalMemorySpace[CoreMemory_SpaceList[i].startAddress + k];
				}
				spacing = 0;
			}
			newPhysicalMemoryUsedByte += CoreMemory_SpaceList[newSpaceQuantity].size;
			newSpaceQuantity++;
		}
		else{
			needMove = TRUE;
			spacing += CoreMemory_SpaceList[i].size;
		}
	}
	CoreMemory_PhysicalMemoryUsedByte = newPhysicalMemoryUsedByte;
	CoreMemory_SpaceCurrentQuantity = newSpaceQuantity;
	//Had bad efficiency, but more safety
	for(i = 0; i < CoreMemory_SpaceCurrentQuantity; i++){
		CoreMemory_SpaceList[i].lock = FALSE;
	}
	return TRUE;
}

Data_Boolean CoreMemory_DropMemory(void){
	Data_1Byte i, j;
	CoreMemory_Size k;
	for(i = 0; i < CoreMemory_SpaceCurrentQuantity; i++){
		if(CoreMemory_SpaceList[i].lock == FALSE || CoreMemory_SpaceList[i].used == FALSE){
			CoreMemory_SpaceList[i].lock = TRUE;
		}
		else{
			for(j = i - 1; ; j--){
				CoreMemory_SpaceList[j].lock = FALSE;
				if(j == 0){
					break;
				}
			}
			return FALSE;
		}
	}
	for(k = 0; k < CoreMemory_ExternalMemorySize; k++){
		CoreMemory_PhysicalMemorySpace[k] = 0x00;
	}
	for(i = 0; i < CoreMemory_SpaceCurrentQuantity; i++){
		CoreMemory_SpaceList[i].used = FALSE;
	}
	CoreMemory_SpaceCurrentQuantity = 0;
	return TRUE;
}

CoreMemory_Space* CoreMemory_CreateSpace(Data_1Byte type, CoreMemory_Size size, Data_1Byte elementSize){
	if(CoreMemory_SpaceCurrentQuantity < CoreMemory_SpaceQuantity && (size + CoreMemory_PhysicalMemoryUsedByte) <= CoreMemory_ExternalMemorySize && size % elementSize == 0){
		CoreMemory_Space* space = &CoreMemory_SpaceList[CoreMemory_SpaceCurrentQuantity];
		space->used = TRUE;
		space->type = type;
		space->lock = FALSE;
		space->startAddress = CoreMemory_PhysicalMemoryUsedByte;
		space->size = size;
		CoreMemory_PhysicalMemoryUsedByte += size;
		space->elementSize = elementSize;
		space->startPoint = 0;
		space->endPoint = 0;
		space->usedSize = 0;
		space->eventJob[0] = CoreScheduler_JobCapability;
		space->eventJob[1] = CoreScheduler_JobCapability;
		space->eventJob[2] = CoreScheduler_JobCapability;
		CoreMemory_SpaceCurrentQuantity++;
		return space;
	}
	return NULL;
}

Data_Boolean CoreMemory_DeleteSpace(CoreMemory_Space* space){
	if(space->lock == FALSE){
		space->lock = TRUE;
		space->used = FALSE;
		return TRUE;
	}
	return FALSE;
}

Data_Boolean CoreMemory_DropSpace(CoreMemory_Space* space){
	if(space->lock == FALSE){
		CoreMemory_Size i, endAddress = space->startAddress + space->size;
		space->lock = TRUE;
		for(i = space->startAddress; i < endAddress; i++){
			CoreMemory_PhysicalMemorySpace[i] = 0x00;
		}
		space->startPoint = 0;
		space->endPoint = 0;
		space->usedSize = 0;
		space->lock = FALSE;
		return TRUE;
	}
	return FALSE;
}

Data_Boolean CoreMemory_Push(CoreMemory_Space* space, CoreMemory_Size index, void *data){
	if(space->lock == FALSE){
		space->lock = TRUE;
		Data_1Byte* inputData = (Data_1Byte*)data;
		Data_1Byte i, dataStartAddress;
		switch(space->type){
			case CoreMemory_SpaceTypeFIFO:{
				if(space->usedSize + space->elementSize <= space->size){
					dataStartAddress = space->startAddress + (space->endPoint);
					for(i = 0; i < space->elementSize; i++){
						CoreMemory_PhysicalMemorySpace[dataStartAddress + i] = inputData[i];
					}
					space->usedSize += space->elementSize;
					space->endPoint = (space->endPoint + space->elementSize) % space->size;
					if(space->size == space->usedSize){
						CoreScheduler_NeedToWork(space->eventJob[CoreMemory_EventHandlerTypeFull]);
					}
				}
				else{
					space->lock = FALSE;
					return FALSE;
				}
				break;
			}
			
			case CoreMemory_SpaceTypeCircularBuffer:{
				dataStartAddress = space->startAddress + (space->endPoint);
				for(i = 0; i < space->elementSize; i++){
					CoreMemory_PhysicalMemorySpace[dataStartAddress + i] = inputData[i];
				}
				space->endPoint = (space->endPoint + space->elementSize) % space->size;
				space->usedSize += space->elementSize;
				if(space->usedSize > space->size){
					space->usedSize = space->size;
					space->startPoint = (space->startPoint + space->elementSize) % space->size;
					CoreScheduler_NeedToWork(space->eventJob[CoreMemory_EventHandlerTypeCross]);
				}
				break;
			}
			
			case CoreMemory_SpaceTypeStack:{
				if(space->usedSize + space->elementSize <= space->size){
					dataStartAddress = space->startAddress + (space->endPoint);
					for(i = 0; i < space->elementSize; i++){
						CoreMemory_PhysicalMemorySpace[dataStartAddress + i] = inputData[i];
					}
					space->usedSize += space->elementSize;
					space->endPoint = space->endPoint + space->elementSize;
					if(space->size == space->usedSize){
						CoreScheduler_NeedToWork(space->eventJob[CoreMemory_EventHandlerTypeFull]);
					}
				}
				else{
					space->lock = FALSE;
					return FALSE;
				}
				break;
			}
			
			case CoreMemory_SpaceTypeArray:{
				if(index < (space->size / space->elementSize)){
					dataStartAddress = space->startAddress + (index * space->elementSize);
					for(i = 0; i < space->elementSize; i++){
						CoreMemory_PhysicalMemorySpace[dataStartAddress + i] = inputData[i];
					}
				}
				else{
					space->lock = FALSE;
					return FALSE;
				}
				break;
			}
		}
		space->lock = FALSE;
		return TRUE;
	}
	return FALSE;
}

Data_Boolean CoreMemory_Pop(CoreMemory_Space* space, CoreMemory_Size index,void *data){
	Data_1Byte* outputData = (Data_1Byte*)data;
	Data_1Byte i, dataStartAddress;
	switch(space->type){
		case CoreMemory_SpaceTypeFIFO:
		case CoreMemory_SpaceTypeCircularBuffer:
			if(space->usedSize != 0){
				dataStartAddress = space->startAddress + (space->startPoint);
				for(i = 0; i < space->elementSize; i++){
					outputData[i] = CoreMemory_PhysicalMemorySpace[dataStartAddress + i];
				}
				if(space->lock == FALSE){
					space->lock = TRUE;
					space->usedSize -= space->elementSize;
					space->startPoint = (space->startPoint + space->elementSize) % space->size;	
					space->lock = FALSE;
					if(space->usedSize == 0){
						CoreScheduler_NeedToWork(space->eventJob[CoreMemory_EventHandlerTypeEmpty]);
					}
				}
				else{
					return FALSE;
				}
			}
			else{
				return FALSE;
			}
			break;
		
		case CoreMemory_SpaceTypeStack:{
			if(space->usedSize != 0){
				dataStartAddress = space->startAddress + (space->endPoint) - space->elementSize;
				for(i = 0; i < space->elementSize; i++){
					outputData[i] = CoreMemory_PhysicalMemorySpace[dataStartAddress + i];
				}
				if(space->lock == FALSE){
					space->lock = TRUE;
					space->usedSize -= space->elementSize;
					space->endPoint -= space->elementSize;	
					space->lock = FALSE;
					if(space->usedSize == 0){
						CoreScheduler_NeedToWork(space->eventJob[CoreMemory_EventHandlerTypeEmpty]);
					}
				}
				else{
					return FALSE;
				}
			}
			else{
				return FALSE;
			}
			break;
		}
		case CoreMemory_SpaceTypeArray:{
			if(index < (space->size / space->elementSize)){
				dataStartAddress = space->startAddress + (index * space->elementSize);
				for(i = 0; i < space->elementSize; i++){
					outputData[i] = CoreMemory_PhysicalMemorySpace[dataStartAddress + i];
				}
			}
			else{
				return FALSE;
			}
			break;
		}
	}
	return TRUE;
}

void CoreMemory_SetInterrupt(CoreMemory_Space* space, Data_1Byte interruptType, CoreScheduler_JobID jobId){
	space->eventJob[interruptType] = jobId;
}
