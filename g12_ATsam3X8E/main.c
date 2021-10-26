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
    
    while (1) 
    {
        //WDT->WDT_CR |= 1 << WDT_CR_WDRSTT; // Feed the dog cyanide
        //printf("Hallo\n\r");
    }
    return 0;
}
