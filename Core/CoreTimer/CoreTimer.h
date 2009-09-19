#ifndef CORETIMER_H
#define	CORETIMER_H

#include "../../SystemInformation.h"
#include "../CoreLookUpTable/CoreLookUpTable.h"
#include "../CoreScheduler/CoreScheduler.h"

Data_1Byte	CoreTimer_State;
Data_4Byte	CoreTimer_BaseTimerClock;
//Valued by Hz

void	CoreTimer_Init(Data_4Byte baseTimerClock);
void	CoreTimer_EnableBaseTimer(Data_Boolean enable);

//User Must Deliver CoreTimer_SetBasicTimerByHz(Data_2Byte hz);
//void	CoreTimer_SetBasicTimerByHz(Data_2Byte hz);

void	CoreTimer_RegisterFrequencyDivider(Data_4Byte divider, CoreScheduler_JobID id);
void	CoreTimer_EnableFrequencyDivider(Data_Boolean enable);



#endif
