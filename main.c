#include <util/delay.h>
#include "SystemInformation.h"
#include "Driver/Uart/Uart.h"
#include "Core/CoreScheduler/CoreScheduler.h"
#include "Core/CoreMemory/CoreMemory.h"
#include "Core/CoreTimer/CoreTimer.h"

extern Data_1Byte* CoreMemory_PhysicalMemorySpace;
CoreMemory_Space* space1;
Data_1Byte inputData = 0;

//A Big Bug When ID > 32 It Will NOT Triger
Data_1Byte jobIndex[10] = {
	0,7,9,12,15,19,32,33,64,65
};

void CommandIn(Data_1Byte input){
	//Uart_Transmit(Uart_Uart1DeviceIdentify, input);
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

void Function0(void){
	Data_1Byte i;
	for(i = 0; i < CoreMemory_ExternalMemorySize; i++){
		Uart_Transmit(Uart_Uart1DeviceIdentify, CoreMemory_PhysicalMemorySpace[i]);
	}
}
void Function1(void) {
	CoreMemory_DropMemory();
}
void Function2(void) {
	space1 = CoreMemory_CreateSpace(CoreMemory_SpaceTypeCircularBuffer, 10, 1);
	CoreMemory_SetInterrupt(space1, CoreMemory_EventHandlerTypeEmpty, jobIndex[7]);
	CoreMemory_SetInterrupt(space1, CoreMemory_EventHandlerTypeFull, jobIndex[8]);
	CoreMemory_SetInterrupt(space1, CoreMemory_EventHandlerTypeCross, jobIndex[9]);
	if(space1 == NULL){
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xC7);
	}
	else{
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xB8);
	}
}
void Function3(void) {
	inputData++;
	if(CoreMemory_Push(space1, 0, &inputData) == FALSE){
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xC7);
	}
}
void Function4(void) {
	Data_1Byte output = 0x12;
	if(CoreMemory_Pop(space1, 0, &output) == FALSE){
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
		Uart_Transmit(Uart_Uart1DeviceIdentify, 0xC7);
	}
	else{
		Uart_Transmit(Uart_Uart1DeviceIdentify, output);
	}
}
void Function5(void) { BasicFunction(5); }
void Function6(void) { BasicFunction(6); }
void Function7(void) {
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x01);
}
void Function8(void) {
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0x02);
}
void Function9(void) {
	Uart_Transmit(Uart_Uart1DeviceIdentify, 0xFF);
	//Uart_Transmit(Uart_Uart1DeviceIdentify, 0x03);
}

int main(void ){
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
	//Data_1Byte i;
	//for(i = 0; i < 10; i++) CoreScheduler_AllowRetrigger(jobIndex[i], (i % 2 == 0)?TRUE:FALSE);
#endif
	
	Uart_Uart1RXCompleteInterruptFunction = CommandIn;
	CoreMemory_Init();
	if(CoreMemory_MemorySpaceVerify()){
		Uart_Transmit(Uart_Uart1DeviceIdentify,  0xB8);
	}
	else{
		Uart_Transmit(Uart_Uart1DeviceIdentify,  0xC7);
	}
	CoreTimer_Init();
	CoreTimer_EnableBaseTimer(TRUE);
	CoreScheduler_RunLoop();
	while(1);
	return 0;
}

/*
ISR(TIMER2_OVF_vect){
	//Uart_Transmit(Uart_Uart1DeviceIdentify, 'N');
}
*/
