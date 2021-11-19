#include "sam.h"
#include "../UART/printf-stdarg.h"
#include "../system_config.h"

#if EEFC_DEBUG
#include "../UART/printf-stdarg.h"
#define EEFC_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define EEFC_DEBUG_PRINT(...)
#endif // EEFC_DEBUG

#define PAGE_SIZE 8
#define IAP_ADDRESS IROM_ADDR + 8

static uint32_t read_data[PAGE_SIZE];
static volatile uint32_t *data_pointer;


/**
 * @brief Provides det FCMDE bit from the status register.
 * 
 * @return uint8_t value of FCMDE.
 */
uint8_t eefc_get_FCMDE(void){
	return EFC1->EEFC_FSR & EEFC_FSR_FCMDE;
}

/**
 * @brief Provides the FLOCKE bit from the status register
 * 
 * @return uint8_t value of FLOCKE
 */
uint8_t eefc_get_FLOCKE(void){
	return EFC1->EEFC_FSR & EEFC_FSR_FLOCKE;
}

void eefc_init(void){
	EFC0->EEFC_FMR = EEFC_FMR_FWS(6);
    EFC1->EEFC_FMR = EEFC_FMR_FWS(6); //| EEFC_FMR_FAM; //Sets number of Flash wait
    //states to 6 cycles. Also enables 64-bit access in read mode
}

void eefc_read_flash_descriptor(void){
    __disable_irq();
    EFC1->EEFC_FCR = EEFC_FCR_FCMD_GETD | EEFC_FCR_FKEY_PASSWD;
    if(EFC1->EEFC_FSR & EEFC_FSR_FRDY){
        printf("FL_ID: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_SIZE: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_PAGE_SIZE: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_NB_PLANE: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_PLANE[0]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_NB_LOCK:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[0]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[1]:  %d\n\r", EFC1->EEFC_FRR);
        printf("FL_LOCK[2]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[3]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[4]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[5]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[6]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[7]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[8]:  %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[9]:  %d\n\r", EFC1->EEFC_FRR);
        printf("FL_LOCK[10]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[11]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[12]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[13]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[14]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[15]: %d\n\r", EFC1->EEFC_FRR);
		printf("FL_LOCK[16]: %d\n\r", EFC1->EEFC_FRR);
        printf("END WORD: %d\n\r", EFC1->EEFC_FRR);
    }

    __enable_irq();
}

uint32_t *eefc_read_single_page(uint16_t page_number){
	volatile uint32_t data_buffer[PAGE_SIZE];

    __disable_irq();
	EFC1->EEFC_FMR |= EEFC_FMR_SCOD;
    EFC1->EEFC_FCR = EEFC_FCR_FCMD_STUI | EEFC_FCR_FKEY_PASSWD;

    while(EFC1->EEFC_FSR & EEFC_FSR_FRDY){
    }

	data_pointer = (uint32_t*)(IFLASH0_ADDR + IFLASH0_PAGE_SIZE*page_number);
	for(uint8_t i = 0; i < PAGE_SIZE; ++i){
		data_buffer[i] = (*data_pointer++);
		EEFC_DEBUG_PRINT("READ DATA: %d\n\r", data_buffer[i]);
	}
	
	EFC1->EEFC_FCR = EEFC_FCR_FCMD_SPUI | EEFC_FCR_FKEY_PASSWD;
	while(!(EFC1->EEFC_FSR & EEFC_FSR_FRDY)){
	}
	EFC1->EEFC_FMR &= ~(EEFC_FMR_SCOD);
    __enable_irq();
	
	return data_buffer;
}

void eefc_write_page(uint16_t page_number, uint32_t* data){
	
    __disable_irq();
    data_pointer = (uint32_t*)(IFLASH0_ADDR + IFLASH0_PAGE_SIZE*page_number);
    for(uint8_t i = 0; i < PAGE_SIZE; ++i){
        *data_pointer++ = data[i];
		EEFC_DEBUG_PRINT("WRITTEN DATA: %d\n\r", data[i]);
    }
	EEFC_DEBUG_PRINT("FCMDE: %d\n\r", eefc_get_FCMDE());
	EEFC_DEBUG_PRINT("FLOCKE: %d\n\r", eefc_get_FLOCKE());
	EFC0->EEFC_FCR = EEFC_FCR_FARG(page_number) | EEFC_FCR_FCMD_EWP | EEFC_FCR_FKEY_PASSWD;
	
	while(!(EFC0->EEFC_FSR & EEFC_FSR_FRDY)){
	}
    
    __enable_irq();
}
