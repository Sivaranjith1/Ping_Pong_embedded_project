/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>

#include "system_config.h"
#include "USART/usart.h"
#include "XMEM/xmem.h"

int main(void)
{
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();
  uint32_t error = 0;
  uint32_t total = 0;

  while(1){
	  /*
	xmem_write(0x10, 0x800);
	uint8_t reading = xmem_read(0x800);
	++total;
	if(reading != 0x10) error++;
	
	if(error != 0)
		printf("Reed %d \n", error);
		*/
	xmem_SRAM_test();
  }

  return 0;
}

