#include "spi.h"

#include <avr/io.h>
#include "../GPIO/gpio.h"

#define CHIP_SELECT PINB4
#define DD_MOSI PINB5
#define DD_MISO PINB6
#define DD_SCK PINB7
#define ALL_INT_CONTROL 10

void spi_init(void){
    unsigned char val = 0x00;
	DDRB = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << CHIP_SELECT);
    val &= 1 << DD_MISO;
	DDRB &= ~val;
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    gpio_pin_enable(4, PORTB);
}

void spi_interrupt_init(void){
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
    spi_transmit(0xFF);
    return SPDR;
}