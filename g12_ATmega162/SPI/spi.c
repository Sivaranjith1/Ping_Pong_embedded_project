#include "spi.h"

#include <avr/io.h>
#include "../GPIO/gpio.h"

#define DD_MOSI PINB5
#define DD_SCK PINB7
#define ALL_INT_CONTROL 0b1010

void spi_init(void){
	DDRB = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << PINB4);
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    gpio_pin_enable(4, PORTB);
}

void interrupt_init(void){
    SREG = (1 << 8);
    MCUCR = 0x00 | ALL_INT_CONTROL;
    GICR = (1 << INT1) | (1 << INT0) | (1 << INT2);
}

void spi_transmit(unsigned char data)
{
    /* Start transmission */
    gpio_pin_disable(4, PORTB);
    SPDR = data;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
    gpio_pin_enable(4, PORTB);
}

unsigned char spi_receive(void){
    spi_transmit(0x00);
    return SPDR;
}