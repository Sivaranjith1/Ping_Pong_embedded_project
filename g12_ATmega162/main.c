/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>

#include "system_config.h"
#include "USART/usart.h"
#include <stdlib.h>


void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

int main(void)
{
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  FILE* output = fdevopen(usart_putchar, 0);
  
  SRAM_test();
  /*
  Keeping this to show how I tested that the latch was in fact plugged in correctly.
  Feel free to delete if you don't need it, disagree or whatever - Ask
  
  uint16_t address = 0x2000;
  unsigned char *p = (unsigned char *) (address + 1);
  DDRC = 0xFF;
  PORTC = 0x00;
  while(1){
	  MCUCR |= (1 << SRE);
	  
	  SFIOR = (1 << XMM1) | (1 << XMM0);
	  *p = 0xaa;
	  
	  SFIOR = 0x00;
	  
	  *p = 0x55;
	  
	  MCUCR = 0x00;
  };
  */
  while(1);
  return 0;
}

