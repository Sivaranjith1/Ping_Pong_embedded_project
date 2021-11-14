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
#include "TIMER/timer.h"
#include "INTERRUPTS/interrupts.h"

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
  joystick_init();
  interrupt_init();
  timer_init();
  spi_init();
  mcp_init();
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
  pos_set_offset_calibration(JOYSTICK_Y);
  pos_set_offset_calibration(JOYSTICK_X);
  while(1){
    //xmem_SRAM_test();
    uint8_t pos_x = adc_get_channel_data((uint8_t)JOYSTICK_X);
    uint8_t pos_y = adc_get_channel_data((uint8_t)JOYSTICK_Y) - 35;
    uint8_t slider_l = adc_get_channel_data((uint8_t)SLIDER_L);
    uint8_t slider_r = adc_get_channel_data((uint8_t)SLIDER_R);
    printf("pos data %d, %d, %d, %d\n", pos_x, pos_y, slider_l, slider_r);
    //for (uint64_t i = 0; i < 50000; i++);
    
  }
  return 0;
}

