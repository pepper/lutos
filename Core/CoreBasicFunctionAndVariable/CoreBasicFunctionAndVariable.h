#ifndef	COREBASICFUNCTIONANDVARIABLEble_H
#define	COREBASICFUNCTIONANDVARIABLEble_H

#include "../../SystemInformation.h"

#define	ClearBit(data,bit)	(data = (data & (~(1 << bit))))
#define	SetBit(data,bit)	(data = (data | (1 << bit)))
#define	GetBit(data,bit)	((data & (1 << bit)) >> bit)
#define	SwapBit(data,bit)	((GetBit(data,bit))?ClearBit(data,bit):SetBit(data,bit))

#ifndef INLINE
# if __GNUC__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif

#endif
