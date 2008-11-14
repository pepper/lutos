#ifndef CAN_H
#define CAN_H

#include "../../SystemInformation.h"
#include "../../Core/CoreBasicTypeDefine.h"
#include "../../Core/CoreBasicFunction/CoreBasicFunction.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define	Can_MObQuantity	15

#define	Can_Reset()		{ CANGCON = 0x01; }
#define	Can_Enable()	{ SetBit(CANGCON, ENASTB); }

void Can_BitTimingSetting(void);

#endif