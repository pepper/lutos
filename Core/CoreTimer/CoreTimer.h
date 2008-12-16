#ifndef CORETIMER_H
#define	CORETIMER_H

#include "../../SystemInformation.h"
#include "../CoreMemory/CoreMemory.h"
#include "../CoreScheduler/CoreScheduler.h"

#if defined(SystemInformation_DeviceAT90CAN128)
//use Timer1
#endif

struct CoreTimer_FrequencyDivider{
	Data_4Byte		divder;
	Data_Boolean	enable;
};
typedef struct CoreTimer_FrequencyDivider CoreTimer_FrequencyDivider;

Data_1Byte	CoreTimer_State;
Data_4Byte	CoreTimer_BaseTimerClock;
//Valued by Hz

CoreTimer_FrequencyDivider*	CoreTimer_FrequencyDividerList;
Data_1Byte					CoreTimer_FrequencyDividerQuantity;

void	CoreTimer_Init(Data_4Byte baseTimerClock, Data_1Byte frequencyDividerQuantity);
void	CoreTimer_EnableBaseTimer(Data_Boolean enable);
void	CoreTimer_FindBaseTimeClock(void);

//User Must Deliver CoreTimer_SetBasicTimerByHz(Data_2Byte hz);

void	CoreTimer_RegisterFrequencyDivider(Data_4Byte divider, CoreScheduler_JobID id);
void	CoreTimer_EnableFrequencyDivider(Data_Boolean enable);

#endif
