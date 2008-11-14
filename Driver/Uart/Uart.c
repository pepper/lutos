#include "Uart.h"

void Uart_Init(void){
	#if defined(Uart_Uart0RXCompleteInterruptEnable) || \
		defined(Uart_Uart0TXCompleteInterruptEnable) || \
		defined(Uart_Uart0DataRegisterEmptyInterruptEnalbe) || \
		defined(Uart_Uart1RXCompleteInterruptEnable) || \
		defined(Uart_Uart1TXCompleteInterruptEnable) || \
		defined(Uart_Uart1DataRegisterEmptyInterruptEnalbe)
		sei();
	#endif
	#ifdef Uart_Uart0Device
		UCSR0B = 0x00
		#ifdef Uart_Uart0RXCompleteInterruptEnable
			| (1 << RXCIE0)
		#endif
		#ifdef Uart_Uart0TXCompleteInterruptEnable
			| (1 << TXCIE0)
		#endif
		#ifdef Uart_Uart0DataRegisterEmptyInterruptEnalbe
			| (1 << UDRIE0)
		#endif
		#ifdef Uart_Uart0ReceiverEnable
			| (1 << RXEN0)
		#endif
		#ifdef Uart_Uart0TransmitterEnable
			| (1 << TXEN0)
		#endif
		#ifdef Uart_Uart09BitCharacterBit
			| (1 << UCSZ02)
		#endif
		;
		UCSR0C = 0x00
		#ifdef Uart_Uart0SynchronousMode
			| (1 << UMSEL0)
		#endif
		#ifdef Uart_Uart0EvenParityMode
			| (1 << UPM01)
		#endif
		#ifdef Uart_Uart0OddParityMode
			| (1 << UPM01) | (1 << UPM00)
		#endif
		#ifdef Uart_Uart02StopBit
			| (1 << USBS0)
		#endif
		#ifdef Uart_Uart06BitCharacterBit
			| (1 << UCSZ00)
		#endif
		#ifdef Uart_Uart07BitCharacterBit
			| (1 << UCSZ01)
		#endif
		#ifdef Uart_Uart08BitCharacterBit
			| (1 << UCSZ01) | (1 << UCSZ00)
		#endif
		#ifdef Uart_Uart09BitCharacterBit
			| (1 << UCSZ01) | (1 << UCSZ00)
		#endif
		#ifdef Uart_Uart0ClockPolarityTransmitRising
			| (1 << UCPOL0)
		#endif
		;
		UBRR0H = (Data_1Byte)((SystemInformation_SystemClock / (Uart_Uart0BaudRate * 16L) -1) >> 8);
		UBRR0L = (Data_1Byte)(SystemInformation_SystemClock / (Uart_Uart0BaudRate * 16L) -1);
	#endif
	#ifdef Uart_Uart1Device
		UCSR1B = 0x00
		#ifdef Uart_Uart1RXCompleteInterruptEnable
			| (1 << RXCIE1)
		#endif
		#ifdef Uart_Uart1TXCompleteInterruptEnable
			| (1 << TXCIE1)
		#endif
		#ifdef Uart_Uart1DataRegisterEmptyInterruptEnalbe
			| (1 << UDRIE1)
		#endif
		#ifdef Uart_Uart1ReceiverEnable
			| (1 << RXEN1)
		#endif
		#ifdef Uart_Uart1TransmitterEnable
			| (1 << TXEN1)
		#endif
		#ifdef Uart_Uart19BitCharacterBit
			| (1 << UCSZ12)
		#endif
		;
		UCSR1C = 0x00
		#ifdef Uart_Uart1SynchronousMode
			| (1 << UMSEL1)
		#endif
		#ifdef Uart_Uart1EvenParityMode
			| (1 << UPM11)
		#endif
		#ifdef Uart_Uart1OddParityMode
			| (1 << UPM11) | (1 << UPM10)
		#endif
		#ifdef Uart_Uart12StopBit
			| (1 << USBS1)
		#endif
		#ifdef Uart_Uart16BitCharacterBit
			| (1 << UCSZ10)
		#endif
		#ifdef Uart_Uart17BitCharacterBit
			| (1 << UCSZ11)
		#endif
		#ifdef Uart_Uart18BitCharacterBit
			| (1 << UCSZ11) | (1 << UCSZ10)
		#endif
		#ifdef Uart_Uart19BitCharacterBit
			| (1 << UCSZ11) | (1 << UCSZ10)
		#endif
		#ifdef Uart_Uart1ClockPolarityTransmitRising
			| (1 << UCPOL1)
		#endif
		;
		UBRR1H = (Data_1Byte)((SystemInformation_SystemClock / (Uart_Uart1BaudRate * 16L) -1) >> 8);
		UBRR1L = (Data_1Byte)(SystemInformation_SystemClock / (Uart_Uart1BaudRate * 16L) -1);
	#endif
}

void Uart_Transmit(Data_1Byte device, Data_1Byte data){
	if(device == Uart_Uart0DeviceIdentify){
		while( !( UCSR0A & (1 << UDRE)) );
		UDR0 = data;
		return;
	}
	else if(device == Uart_Uart1DeviceIdentify){
		while( !( UCSR1A & (1 << UDRE)) );
		UDR1 = data;
		return;
	}
}

void Uart_TransmitStream(Data_1Byte device, Data_1Byte* dataStream, Data_4Byte dataLength){
	while(dataLength > 0){
		Uart_Transmit(device, dataStream[dataLength]);
		dataLength--;
	}
}

Data_1Byte Uart_Receive(Data_1Byte device){
	if(device == Uart_Uart0DeviceIdentify){
		while( !( UCSR0A & (1 << RXC)) );
		return UDR0;
	}
	else if(device == Uart_Uart1DeviceIdentify){
		while( !( UCSR1A & (1 << RXC)) );
		return UDR1;
	}
	return 0;
}

#if defined(Uart_Uart0RXCompleteInterruptEnable)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART0_RX_vect){
			Uart_Uart0RXCompleteInterruptFunction(UDR0);
		}
	#endif
#endif
#if defined(Uart_Uart0TXCompleteInterruptEnable)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART0_TX_vect){
			Uart_Uart0TXCompleteInterruptFunction();
		}
	#endif
#endif
#if defined(Uart_Uart0DataRegisterEmptyInterruptEnalbe)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART0_UDRE_vect){
			Uart_Uart0DataRegisterEmptyInterruptFunction();
		}
	#endif
#endif

#if defined(Uart_Uart1RXCompleteInterruptEnable)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART1_RX_vect){
			Uart_Uart1RXCompleteInterruptFunction(UDR1);
		}
	#endif
#endif
#if defined(Uart_Uart1TXCompleteInterruptEnable)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART1_TX_vect){
			Uart_Uart1TXCompleteInterruptFunction();
		}
	#endif
#endif
#if defined(Uart_Uart1DataRegisterEmptyInterruptEnalbe)
	#if defined(Uart_TwoSerialPortDevice)
		ISR(USART1_UDRE_vect){
			Uart_Uart1DataRegisterEmptyInterruptFunction();
		}
	#endif
#endif
