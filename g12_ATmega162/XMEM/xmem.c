/*
 * CFile1.c
 *
 * Created: 07.09.2021 12:47:12
 *  Author: sivarans
 */ 
#include "xmem.h"
#include <avr/io.h>

#define BASE_ADRESS 0x1000

void xmem_init(void){
	  MCUCR |= (1 << SRE);
	  DDRC = 0xFF;
	  PORTC = 0x00;
	  SFIOR |= (1 << XMM2);
}

void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem = (char *)BASE_ADRESS;
	ext_mem[addr] = data;
}

uint8_t xmem_read(uint16_t addr){
	volatile char *ext_mem = (char *)BASE_ADRESS;
	uint8_t ret_val = ext_mem[addr];
	return ret_val;
}