#include "sam.h"

uint8_t read_flag = 0;
uint8_t write_flag = 0;

uint32_t write_data[4];
uint32_t read_data[4];
volatile uint32_t *data_buffer;

void eefc_init(void){
    EFC0->EEFC_FMR = EEFC_FMR_FRDY; //Enables interrupt on RDRY Signal
    NVIC_EnableIRQ(ID_EFC0);
}

void eefc_write(uint16_t page_number, uint32_t data){
    EFC0->EEFC_FCR = EEFC_FCR_FARG(page_number) | EEFC_FCR_FKEY_PASSWD;
	EFC0->EEFC_FCR = EEFC_FCR_FCMD_EWP | EEFC_FCR_FKEY_PASSWD;

}

void eefc_read_single_page(uint16_t page_number){
    read_flag = 1;
    data_buffer = (uint32_t *)IFLASH0_ADDR;
    EFC0->EEFC_FCR = EEFC_FCR_FARG(page_number) | EEFC_FCR_FCMD_STUI | EEFC_FCR_FKEY_PASSWD;  
}

void EFC0_Handler(void)
{
    printf("FLASH Interrupt\n\r");
    if (read_flag){
        read_data[0] = &data_buffer;
        read_flag = 0;
        EFC0->EEFC_FCR = EEFC_FCR_FCMD_SPUI | EEFC_FCR_FKEY_PASSWD;
    }

	
	NVIC_ClearPendingIRQ(ID_EFC0);
}