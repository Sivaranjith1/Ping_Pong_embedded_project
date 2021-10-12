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


void init(void){
    configure_uart();
    can_init_def_tx_rx_mb(CAN_BR_VALUES);
}

int main(void)
{
    /* Initialize the SAM system */
	
    SystemInit();
    init();
	printf("We should make it print something\n\r");
    CAN_MESSAGE message = {
        .id = {69},
        .data_length = 2,
        .data = {420, 420}
    };
    WDT->WDT_MR = WDT_MR_WDDIS;
    while (1) 
    {
        //WDT->WDT_CR |= 1 << WDT_CR_WDRSTT; // Feed the dog cyanide
        //can_send(&message, 0);
        //printf("Hallo\n\r");
    }
    return 0;
}
