/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
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

int main(void)
{
  init();
  printf("Hello world eller noe sånt\n");
  can_frame_t test_frame = {
    .id = 0x19,
    .rtr = 0,
    .data_len = 1,
    .data = {69}
  };

  can_frame_t test_frame_2;

  can_transmit(&test_frame);
  can_receive(0, &test_frame_2);
  while(1){
    //joystick_read();
    //joystick_read_button_polled();

    
    printf("id: %x \n",test_frame_2.id);
    printf("length: %x \n",test_frame_2.data_len);
    for(uint8_t i = 0; i < 8; i++){
      printf("data: %d \n",test_frame_2.data[i]);
    }
    //printf("%x \n", mcp_read(MCP_RXB0SIDL));
  }
  return 0;
}

