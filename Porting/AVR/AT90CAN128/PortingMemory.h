#ifndef	PORTINGMEMORY_H
#define	PORTINGMEMORY_H

#include <avr/pgmspace.h>

#define Porting_StoreInProgramMemory					PROGMEM
#define Porting_Read1ByteFromProgramMemory(ADDRESS)		pgm_read_byte(&(ADDRESS))
#define Porting_Read2ByteFromProgramMemory(ADDRESS)		pgm_read_dword(&(ADDRESS))

//#deifne	Porting_StoreInExternalMemory
#define	Porting_ExternalMemoryInit()	{	\
	XMCRA = 0x00;							\
	XMCRB = 0x01;							\
	XMCRA = XMCRA | (0x80);					\
	DDRC = DDRC | (0x80);					\
	PORTC = PORTC & (0x7F);					\
}											\

#endif
