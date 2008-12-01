#include <util/delay.h>
#include "Core/CoreBasicTypeDefine.h"
#include "Driver/Uart/Uart.h"
#include "Core/CoreScheduler/CoreScheduler.h"

void CommandIn(Data_1Byte input){
	Uart_Transmit(Uart_Uart1DeviceIdentify, input);
	switch(input){
		case '1':
		case '2':
		case '3':
		case '4':
			CoreScheduler_NeedToWork(input - '1');
			break;
	}
}

void FunctionA(void){
	PORTE = 0x01;
	_delay_ms(1000.0f);
	Data_1Byte i;
	for(i = 0; i < 1; i++){
		PORTE = 0x0A;
		_delay_ms(300.0f);
		PORTE = 0x0B;
		_delay_ms(300.0f);
	}
	PORTE = 0x0F;
}
void FunctionB(void){
	PORTE = 0x02;
	_delay_ms(1000.0f);
	Data_1Byte i;
	for(i = 0; i < 2; i++){
		PORTE = 0x0A;
		_delay_ms(300.0f);
		PORTE = 0x0B;
		_delay_ms(300.0f);
	}
	PORTE = 0x0F;
	
}
void FunctionC(void){
	PORTE = 0x03;
	_delay_ms(1000.0f);
	Data_1Byte i;
	for(i = 0; i < 3; i++){
		PORTE = 0x0A;
		_delay_ms(300.0f);
		PORTE = 0x0B;
		_delay_ms(300.0f);
	}
	PORTE = 0x0F;
}
void FunctionD(void){
	PORTE = 0x04;
	_delay_ms(1000.0f);
	Data_1Byte i;
	for(i = 0; i < 4; i++){
		PORTE = 0x0A;
		_delay_ms(300.0f);
		PORTE = 0x0B;
		_delay_ms(300.0f);
	}
	PORTE = 0x0F;
	
}

int main(void ){
	DDRE = 0xFF;
	DDRD = 0xFF;
	PORTD = 0xFF;
	/*Data_1Byte Portd = 0x01;
	PORTD = ~Portd;
	_delay_ms(300.0f);
	Portd = Portd << 1;
	PORTD = ~Portd;
	_delay_ms(300.0f);
	Portd = Portd << 1;
	PORTD = ~Portd;
	_delay_ms(300.0f);
	Portd = Portd << 1;
	PORTD = ~Portd;
	_delay_ms(300.0f);
	*/
	Uart_Init();
	CoreScheduler_Init();
	CoreScheduler_RegisterJob(0, FunctionA);
	CoreScheduler_AllowRetrigger(0, TRUE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'A');
	CoreScheduler_RegisterJob(1, FunctionB);
	CoreScheduler_AllowRetrigger(1, FALSE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'B');
	CoreScheduler_RegisterJob(2, FunctionC);
	CoreScheduler_AllowRetrigger(2, TRUE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'C');
	CoreScheduler_RegisterJob(3, FunctionD);
	CoreScheduler_AllowRetrigger(3, FALSE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'D');
	Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_JobTreeLeaf[0].jobAllowRetrigMask);
	
	Uart_Uart1RXCompleteInterruptFunction = CommandIn;
	CoreScheduler_JobTreeLeaf[0].jobExecuteFunction[0]();
	_delay_ms(300.0f);
	CoreScheduler_JobTreeLeaf[0].jobExecuteFunction[1]();
	_delay_ms(300.0f);
	CoreScheduler_JobTreeLeaf[0].jobExecuteFunction[2]();
	_delay_ms(300.0f);
	CoreScheduler_JobTreeLeaf[0].jobExecuteFunction[3]();
	_delay_ms(300.0f);
	CoreScheduler_RunLoop();
	while(1);
	return 0;
}
