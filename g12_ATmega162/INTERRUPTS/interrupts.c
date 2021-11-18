#include "interrupts.h"

void interrupt_init(){
    cli(); // disable global interrupt
    GICR = (1 << INT2); // enable interrupt for pin INT2
    //MCUCR = (1 << ISC11);
    EMCUCR = 1; // external interrupt enable on INT2
    GIFR = (1 << INTF2);  // clear flags
    sei(); // enable global interrupt
}