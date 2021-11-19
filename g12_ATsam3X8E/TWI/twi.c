#include "twi.h"
#include "sam.h"

#define RPI_ADDRESS 0xA


void twi_init(){
    // Set-up for TWI0 clock
    PIOA->PIO_PDR |= PIO_PDR_P18;
    PIOA->PIO_ABSR |= PIO_ABSR_P18;

    // Set-up for TWI0 data
    PIOA->PIO_PDR |= PIO_PDR_P17;
    PIOA->PIO_ABSR |= PIO_ABSR_P17;

    // PMC set-up for TWI0
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TWI0 << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= (1 << ID_TWI0);

    // Want T_low = T_high = 8*T_mck
    TWI0->TWI_CWGR |= TWI_CWGR_CLDIV(1) | TWI_CWGR_CHDIV(1) | TWI_CWGR_CKDIV(2);

    // Disable slave mode, enable master mode
    TWI0->TWI_CR |= TWI_CR_MSEN | TWI_CR_SVDIS;

    // Setting the master mode to write to RPI
    TWI0->TWI_MMR = TWI_MMR_DADR(RPI_ADDRESS);

    // Enable transmission complete interrupt
    TWI0->TWI_IER |= TWI_IER_NACK;
    NVIC_EnableIRQ(TWI0_IRQn);

}

void twi_send_byte(uint8_t data){
    TWI0->TWI_THR = data;
    TWI0->TWI_CR |= TWI_CR_STOP;
}

void TWI0_Handler(){
    uint16_t status = TWI0->TWI_SR;
    uint16_t rxh = TWI0->TWI_THR;
    //printf("Status register value %d:\n\r", status);
    //printf("RHR register value: %d \n\r", rxh);
    NVIC_ClearPendingIRQ(TWI0_IRQn);
}
