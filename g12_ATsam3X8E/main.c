/*
 * g12_ATsam3X8E.c
 *
 * Created: 05.10.2021 14:23:49
 * Author : sivarans
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


void init(void){
    SystemInit();
    configure_uart();
    can_init_def_tx_rx_mb(CAN_BR_VALUES);
    pwm_init();
    adc_init();
}

int main(void)
{
    /* Initialize the SAM system */

    init();
    //pwm_update_duty_cycle(50, 6);
	printf("We should make it print something\n\r");
    
    WDT->WDT_MR = WDT_MR_WDDIS;
    
    adc_start_conversion();
    while (1) 
    {
        if(goal_check_for_goal()){
            printf("GOOOOOOOAL %d \n\r", goal_get_goals());
            for (uint16_t i = 0; i < 10000; i++);
        }
        /*
        for (uint32_t i = 0; i < 100000; i++);
        float data = adc_get_data(0);
        printf("Here is some data bitches %d \n\r", (uint32_t) data * 1000);
        printf("Bert, convert: %d \n\r", (uint32_t)adc_get_ema_filtered_data(0, 0.6) * 1000);
        */
    }
    return 0;
}
