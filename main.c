#include <util/delay.h>
#include "Core/CoreBasicTypeDefine.h"
#include "Driver/Uart/Uart.h"
#include "Core/CoreScheduler/CoreScheduler.h"

void CommandIn(Data_1Byte input){
	Uart_Transmit(Uart_Uart1DeviceIdentify, input);
	switch(input){
		/*case 0x01:
			Uart_Transmit(Uart_Uart1DeviceIdentify, index);
			CoreScheduler_QueuePush(index++);
			Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_CurrentJobQuantity);
			Uart_Transmit(Uart_Uart1DeviceIdentify, 0xAA);
			break;
			
		case 0x02:
			CoreScheduler_QueuePop();
			Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_CurrentJobQuantity);
			Uart_Transmit(Uart_Uart1DeviceIdentify, 0xBB);
			break;
			
		case 0x03:
			Uart_Transmit(Uart_Uart1DeviceIdentify, 0xAA);
			
			CoreScheduler_QueueItemRef point = CoreScheduler_HeadJob;
			//Show All Item ID
			while(point != CoreScheduler_FootJob && point != NULL){
				Uart_Transmit(Uart_Uart1DeviceIdentify, point->id);
				point = point->next;
			}
			if(point != NULL){
				Uart_Transmit(Uart_Uart1DeviceIdentify, point->id);
			}
			Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
			break;
			
		case 0x04:
			Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_HeadJob->id);
			break;
			
		case 0x05:
			Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_FootJob->id);
			break;
			
		case 0x06:
			Uart_Transmit(Uart_Uart1DeviceIdentify, CoreScheduler_CurrentJobQuantity);
			break;
			
		case 0x07:
			CoreScheduler_QueueEmpty();
			break;
		*/
		case '1':
		case '2':
		case '3':
		case '4':
			CoreScheduler_NeedToWork(input - '1');
			break;
	}
}

void FunctionA(void){
	Uart_Transmit(Uart_Uart1DeviceIdentify, '1' );
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
}
void FunctionB(void){
	Uart_Transmit(Uart_Uart1DeviceIdentify, '2' );
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
}
void FunctionC(void){
	Uart_Transmit(Uart_Uart1DeviceIdentify, '3' );
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
}
void FunctionD(void){
	Uart_Transmit(Uart_Uart1DeviceIdentify, '4' );
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
	_delay_ms(1000.0f);
	Uart_Transmit(Uart_Uart1DeviceIdentify, '.');
}

int main(void ){
	Uart_Init();
	CoreScheduler_Init();
	CoreScheduler_RegisterJob(0, FunctionA);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'A');
	CoreScheduler_RegisterJob(1, FunctionB);
	CoreScheduler_AllowRetrigger(1, FALSE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'B');
	CoreScheduler_RegisterJob(2, FunctionC);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'C');
	CoreScheduler_RegisterJob(3, FunctionD);
	CoreScheduler_AllowRetrigger(3, FALSE);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 'D');
	//index = 0;
	Uart_Uart1RXCompleteInterruptFunction = CommandIn;
	CoreScheduler_RunLoop();
	while(1);
	return 0;
}
