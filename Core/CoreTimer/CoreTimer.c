#include "CoreTimer.h"

void CoreTimer_Init(Data_4Byte baseTimerClock, Data_1Byte frequencyDividerQuantity){
	CoreTimer_BaseTimerClock = baseTimerClock;
	CoreTimer_FrequencyDividerList = CoreMemory_Alloc(sizeof(CoreTimer_FrequencyDivider) * frequencyDividerQuantity);
}
