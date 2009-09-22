#include "CoreTimer.h"

Data_1Byte	CoreTimer_FrequencyDividerState, x = 0;

void CoreTimer_Init(void){
	Porting_BasicTimerInit();
	Porting_SetBasicTimer();
	Porting_GlobalInterruptEnable();
}

void CoreTimer_EnableBaseTimer(Data_Boolean enable){
	if(enable == TRUE){
		Porting_EnableBasicTimer();
	}
	else{
		Porting_DisableBasicTimer();
	}
}

Porting_BasicTimerInterrupt(){
	/*x++;
	if(x >= 100){
		x = 0;
		CoreScheduler_NeedToWork(65);
	}*/
	Porting_ResetBasicTimerCount();
}