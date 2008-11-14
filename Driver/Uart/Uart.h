#ifndef UART_H
#define UART_H


#include "../../SystemInformation.h"
#include "../../Core/CoreBasicTypeDefine.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#if defined(SystemInformation_DeviceATmega128) || defined(SystemInformation_DeviceAT90CAN128)
	#define	Uart_TwoSerialPortDevice
#endif

//#include "Uart.router"
#include "Uart.config"

#if defined(Uart_TwoSerialPortDevice)
	#define	Uart_Uart0DeviceIdentify	0
	#if defined(Uart_Uart0RXCompleteInterruptEnable)
		void (*Uart_Uart0RXCompleteInterruptFunction)(Data_1Byte data);
	#endif
	#if	defined(Uart_Uart0TXCompleteInterruptEnable)
		void (*Uart_Uart0TXCompleteInterruptFunction)(void);
	#endif
	#if	defined(Uart_Uart0DataRegisterEmptyInterruptEnalbe)
		void (*Uart_Uart0DataRegisterEmptyInterruptFunction)(void);
	#endif
	
	#define	Uart_Uart1DeviceIdentify	1
	#if	defined(Uart_Uart1RXCompleteInterruptEnable)
		void (*Uart_Uart1RXCompleteInterruptFunction)(Data_1Byte data);
	#endif
	#if	defined(Uart_Uart1TXCompleteInterruptEnable)
		void (*Uart_Uart1TXCompleteInterruptFunction)(void);
	#endif
	#if	defined(Uart_Uart1DataRegisterEmptyInterruptEnalbe)
		void (*Uart_Uart1DataRegisterEmptyInterruptFunction)(void);
	#endif
#endif

void		Uart_Init(void);
void		Uart_Transmit(Data_1Byte device, Data_1Byte data);
void		Uart_TransmitStream(Data_1Byte device, Data_1Byte* dataStream, Data_4Byte dataLength);
Data_1Byte	Uart_Receive(Data_1Byte device);

#endif
