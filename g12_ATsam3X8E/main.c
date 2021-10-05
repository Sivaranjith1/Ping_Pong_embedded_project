/*
 * g12_ATsam3X8E.c
 *
 * Created: 05.10.2021 14:23:49
 * Author : sivarans
 */ 


#include "sam.h"
#include "CAN/can_controller.h"
#include "CAN/can_interrupt.h"
#include "UART/uart.h"
#include "UART/printf-stdarg.h"

#define CAN_BR 4000000

void init(void){
    configure_uart();
    can_init_def_tx_rx_mb(CAN_BR);
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
    init();
    PIOA->PIO_PER |= (1 << 19) | (1 << 20);
    PIOA->PIO_OER |= (1 << 19) | (1 << 20);
    while (1) 
    {
        PIOA->PIO_SODR |= (1 << 19) | (1 << 20);
        for (uint64_t i = 0; i < (SystemCoreClock/4); i++){};
        PIOA->PIO_CODR |= (1 << 19) | (1 << 20);
        for (uint64_t i = 0; i < (SystemCoreClock/4); i++){};
        printf("Hallo\n\r");
        //uart_putchar('A');
    }
    return 0;
}
