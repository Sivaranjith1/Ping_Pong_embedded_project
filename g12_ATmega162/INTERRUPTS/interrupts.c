#include "interrupts.h"

void interrupt_init(){
    cli(); // disable global interrupt
	//MCUCR = (0 << ISC00); // enable interrupt for falling edge of INT0
    GICR = (1 << INT2) | (1 << INT0); // enable interrupt for pin INT2 and INT0
    EMCUCR = (1 << ISC2); // external interrupt enable on INT2
    GIFR = (1 << INTF2) | (1 << INTF0);  // clear flags
    sei(); // enable global interrupt
}
