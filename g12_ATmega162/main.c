/**
 * @file main.c
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief The main function for running the code of the application
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "system_config.h"
#include "ADC/adc.h"
#include "ADC/joystick.h"
#include "USART/usart.h"
#include "XMEM/xmem.h"
#include "OLED/oled.h"
#include "MENU/menu.h"
#include "GPIO/gpio.h"
#include "SRAM/sram.h"
#include "SPI/spi.h"
#include "CAN/can.h"
#include "CAN/mcp2515.h"
#include "CAN/mcp_constants.h"

/**
 * @brief Run all init functions for different peripherals in one function
 * 
 */
void init(void){
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();
  sram_init();
  oled_init();
  menu_init();
  spi_init();
  mcp_init();
  //spi_interrupt_init();
  can_init();
}

/**
 * @brief The main function with the infinite while loop 
 * 
 */
int main(void)
{
  init();
  printf("Hello world eller noe sånt\n");
  printf("CNF1: %x \n", mcp_read(MCP_CNF1));
  printf("CNF2: %x \n", mcp_read(MCP_CNF2));
  printf("CNF3: %x \n", mcp_read(MCP_CNF3));
  can_frame_t test_frame = {
    .id = 0x19,
    .rtr = 0,
    .data_len = 8,
    .data.f32 = {69.9, 10}
  };

  can_frame_t test_frame_2;

  while(1){
	  /*can_receive(0, &test_frame_2);
	  printf("id: %x \n",test_frame_2.id);
	  printf("length: %x \n",test_frame_2.data_len);
	  for(uint8_t i = 0; i < 8; i++){
	  	printf("data: %d \n",test_frame_2.data[i]);
	  }
	  */
    joystick_read();

	  joystick_can_transmit_pos();
    for (uint32_t i = 0; i < 10000; i++);
    
  }
  return 0;
}

