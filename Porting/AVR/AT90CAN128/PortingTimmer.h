#ifndef	PORTINGTIMMER_H
#define	PORTINGTIMMER_H

//Using Timer 2 as basic timer
#define	Porting_BasicTimerInit()	{																				\
	TCCR2A = (1 << CS20) | (1 << CS21) | (1 << CS22) | (1 << COM2A0) | (0 << COM2A1) | (0 << WGM20) | (1 << WGM21);	\
	ASSR = (0 << EXCLK) | (0 << AS2);																				\
}																													\

//頻率會差了兩倍是因為 Datasheet 上寫的輸出頻率是 OCNX 設為 Troggle 時的輸出頻率，所以 Compare Match 的中斷頻率為 OCNX 頻率的兩倍。
//Set Timmer 2 Prescaler by 1024
//Set Timmer 2 In CTC Mode
//Set Timmer 2 NOT Connected to OC2A
//Disable External Clock Input
//Disable Asynchronous

//Set Timer 2 100Hz
#define Porting_SetBasicTimer()	{	\
	OCR2A = 107;					\
}									\

#define	Porting_ResetBasicTimerCount()	{	\
	TCNT2 = 0;								\
}											\

#define	Porting_EnableBasicTimer()	{	\
	TIMSK2 = (1 << OCIE2A);				\
}										\

#define	Porting_DisableBasicTimer()	{	\
	TIMSK2 = (0 << OCIE2A);				\
}										\

#define	Porting_BasicTimerInterrupt()	ISR(TIMER2_COMP_vect)

#endif
