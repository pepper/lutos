#ifndef	PORTINGMEMORY_H
#define	PORTINGMEMORY_H

#include <avr/pgmspace.h>

#define Porting_StoreInProgramMemory					PROGMEM
#define Porting_ReadByteFromProgramMemory(ADDRESS)		pgm_read_byte(&(ADDRESS))
#define Porting_Read2ByteFromProgramMemory(ADDRESS)		pgm_read_dword(&(ADDRESS))

#endif
