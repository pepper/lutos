#ifndef CORETIMER_H
#define	CORETIMER_H

#include "../../SystemInformation.h"
#include "../CoreLookUpTable/CoreLookUpTable.h"
#include "../CoreScheduler/CoreScheduler.h"

//Data_4Byte	CoreTimer_BaseTimerClock;
//Valued by Hz

void	CoreTimer_Init(void);
void	CoreTimer_EnableBaseTimer(Data_Boolean enable);
void	CoreTimer_RegisterFrequencyDivider(Data_1Byte divider, CoreScheduler_JobID id);
void	CoreTimer_EnableFrequencyDivider(Data_Boolean enable);

#endif
