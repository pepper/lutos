#ifndef	PORTINGTIMMER_H
#define	PORTINGTIMMER_H

#define Porting_SetBasicTimerByHz(HZ)	{																									\
	TCCR2A = (1 << CS20) | (1 << CS21) | (1 << CS22) | (1 << COM2A0) | (0 << COM2A1) | (0 << WGM20) | (1 << WGM21);							\
	ASSR = (0 << EXCLK) | (0 << AS2);																										\
	TIMSK2 = (1 << OCIE2A) | (1 << TOIE2);																									\
	OCR2A = 107;	\
}																																			\
//頻率會差了被是因為 Datasheet 上寫的輸出頻率是 OCNX 設為 Troggle 時的輸出頻率，所以 Compare Match 的中斷頻率為 OCNX 頻率的兩倍。
//Set Timmer 2 Prescaler by 1024
//Set Timmer 2 In CTC Mode
//Set Timmer 2 NOT Connected to OC2A
//Disable External Clock Input
//Disable Asynchronous

#endif
