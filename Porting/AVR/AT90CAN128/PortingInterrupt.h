#ifndef	PORTINGINTERRUPT_H
#define	PORTINGINTERRUPT_H

#include <avr/interrupt.h>

#define	Porting_GlobalInterruptEnable()		sei();
#define	Porting_GlobalInterruptDisable()	cli();
//AVR interrupt triggered by set the interrupt flag, so that event occur during Disable Interrupt time will trig after Enable Interrupt
//For other CPU make sure to check this point !!!
//Enable Interrupt After 4 CPU Clock

#endif
