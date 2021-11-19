/**
 * @file main.c
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief The main application of the ATSAME3X8E for this project
 * @version 1.0 
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "sam.h"
#include "system_config.h"
#include "CAN/can_controller.h"
#include "CAN/can_interrupt.h"
#include "UART/uart.h"
#include "UART/printf-stdarg.h"
#include "PWM/pwm.h"
#include "ADC/adc.h"
#include "ADC/goal_handler.h"
#include "TIMER/timer.h"
#include "DACC/dacc.h"
#include "MOTOR/motor.h"
#include "EEFC/eefc.h"
#include "TWI/twi.h"


/**
 * @brief Run all init functions for different peripherals in one function
 * 
 */
void init(void){
    SystemInit();
    configure_uart();
    can_init_def_tx_rx_mb(CAN_BR_VALUES);
    pwm_init();
    adc_init();
    timer_init();
    dacc_init();
    motor_init();
    eefc_init();
    joystick_init();
    twi_init();
}

/**
 * @brief The main function with the infinite while loop 
 * 
 */
int main(void)
{
    /* Initialize the SAM system */
    init();
	printf("\n\rAtsame starting ...\n\r");
    
    WDT->WDT_MR = WDT_MR_WDDIS;
    //eefc_read_flash_descriptor();
    uint32_t data[8];
    for (int i = 0; i < 8; ++i){
        data[i] = i;
		//printf("DATALOOP \n\r");
    }
  
    //eefc_write(50, data);
    //eefc_read_single_page(50);
    while (1);

    return 0;
}
