#include "sram.h"
#include <stdint.h>
#include "../OLED/oled.h"
#include "../system_config.h"
#include "../XMEM/xmem.h"

void sram_init(void){
    sram_reset();
}

void sram_reset(void){
	for(uint16_t i = OLED_SRAM_ADDRESS_START; i < OLED_SRAM_ADDRESS_END; i++){
        xmem_write(0x00, i);
    }
}
