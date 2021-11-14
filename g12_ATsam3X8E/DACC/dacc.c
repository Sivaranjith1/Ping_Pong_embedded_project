#include "dacc.h"
#include "sam.h"
#include <stdint.h>
#include "../system_config.h"

#if DACC_DEBUG
#define DACC_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DACC_DEBUG_PRINT(...)
#endif // DACC_DEBUG

//void DACC_Handler(void){
//	DACC_DEBUG_PRINT("DACC debugger says hi \n\r");
//	NVIC_ClearPendingIRQ(DACC_IRQn);
//}


void dacc_init(){
    PIOB->PIO_PDR |= PIO_PDR_P16;   // Disables IO on pin 2
	PIOB->PIO_ABSR |= PIO_ABSR_P16; // Selects peripheral on pin 2
	
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_DACC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 |= 1 << (ID_DACC - 32); //enable DACC in PMC

	DACC->DACC_WPMR = (0x444143 << 8); // Disables WP 
	DACC->DACC_MR = DACC_MR_TRGEN_DIS | DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF; //| DACC_MR_SLEEP | DACC_MR_FASTWKUP; //Disables external trigger (for free running mode), enables sleep mode and fast wakeup
    DACC->DACC_CHER = DACC_CHER_CH1; //Enables channel 1 on the dacc
	DACC->DACC_IER = DACC_IER_TXRDY;
	
	//NVIC_EnableIRQ(DACC_IRQn);
}

void dacc_convert(float data){
	uint16_t converted_data = data*4000;
	if((DACC->DACC_ISR & DACC_ISR_TXRDY)){
		DACC_DEBUG_PRINT("DACC debugger says hi: %d \n\r", converted_data);
		DACC->DACC_CDR = (converted_data << DACC_CHDR_CH0);
	}
}