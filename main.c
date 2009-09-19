#include <util/delay.h>
#include "SystemInformation.h"
#include "Driver/Uart/Uart.h"
#include "Core/CoreScheduler/CoreScheduler.h"

//Data_2Byte x;

//A Big Bug When ID > 32 It Will NOT Triger
Data_1Byte jobIndex[10] = {
	0,7,9,12,15,19,32,33,64,65
};

void CommandIn(Data_1Byte input){
	Uart_Transmit(Uart_Uart1DeviceIdentify, input);
	CoreScheduler_NeedToWork(jobIndex[input]);
}

void BasicFunction(Data_1Byte input){
	Uart_Transmit(Uart_Uart1DeviceIdentify, input);
	Data_1Byte i;
	for(i = 0; i < input; i++){
		_delay_ms(300.0f);
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xAA);
	}
}

void Function0(void) { BasicFunction(0); }
void Function1(void) { BasicFunction(1); }
void Function2(void) { BasicFunction(2); }
void Function3(void) { BasicFunction(3); }
void Function4(void) { BasicFunction(4); }
void Function5(void) { BasicFunction(5); }
void Function6(void) { BasicFunction(6); }
void Function7(void) { BasicFunction(7); }
void Function8(void) { BasicFunction(8); }
void Function9(void) { BasicFunction(9); }

int main(void ){
	DDRB = 0xFF;
	DDRE = 0xFF;
	DDRD = 0xFF;
	PORTD = 0xFF;
		
	Uart_Init();
	CoreScheduler_Init();
	CoreScheduler_RegisterJob(jobIndex[0], Function0);
	CoreScheduler_RegisterJob(jobIndex[1], Function1);
	CoreScheduler_RegisterJob(jobIndex[2], Function2);
	CoreScheduler_RegisterJob(jobIndex[3], Function3);
	CoreScheduler_RegisterJob(jobIndex[4], Function4);
	CoreScheduler_RegisterJob(jobIndex[5], Function5);
	CoreScheduler_RegisterJob(jobIndex[6], Function6);
	CoreScheduler_RegisterJob(jobIndex[7], Function7);
	CoreScheduler_RegisterJob(jobIndex[8], Function8);
	CoreScheduler_RegisterJob(jobIndex[9], Function9);
	
#if defined(CoreScheduler_EnableCheckRetrig)
	Data_1Byte i;
	for(i = 0; i < 10; i++) CoreScheduler_AllowRetrigger(jobIndex[i], (i % 2 == 0)?TRUE:FALSE);
#endif
	
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x01);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x02);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x03);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x04);
	
	Uart_Uart1RXCompleteInterruptFunction = CommandIn;
	ClearBit(PORTD, 4);
	Uart_Transmit(Uart_Uart1DeviceIdentify,  0xF0);
	//Porting_SetBasicTimerByHz(100);
	Porting_ExternalMemoryInit();
	CoreScheduler_RunLoop();
	while(1);
	return 0;
}
/*
ISR(TIMER2_COMP_vect){
	x++;
	if(x >= 100){
		x = 0;
		Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
		SwapBit(PORTE, 5);
	}
}

ISR(TIMER2_OVF_vect){
	//Uart_Transmit(Uart_Uart1DeviceIdentify, 'N');
}
*/
