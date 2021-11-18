
#include "highscore.h"
#include "../system_config.h"
#include "../XMEM/xmem.h"


void highscore_init(){
  for (uint8_t i = 0; i < HIGHSCORE_SCORES_NUM; i++)
  {
    xmem_write_with_check(0, HIGHSCORE_SRAM_ADDRESS_START + i);
  }
  
}

void highscore_add_score(uint8_t new_score){
  uint8_t last_value = 0;
  uint8_t last_index = 0;
  for(uint8_t i = 0; i < HIGHSCORE_SCORES_NUM; i++){
    uint8_t val = xmem_read(HIGHSCORE_SRAM_ADDRESS_START + i);
    if(new_score > val){
      last_value = val;
      last_index = i;
      xmem_write_with_check(new_score, HIGHSCORE_SRAM_ADDRESS_START + i);
      break;
    }
  }

  for(uint8_t i = last_index + 1; i < HIGHSCORE_SCORES_NUM; i++){
    uint8_t temp_last = xmem_read(HIGHSCORE_SRAM_ADDRESS_START + i);
    xmem_write_with_check(last_value, HIGHSCORE_SRAM_ADDRESS_START + i);
    last_value = temp_last;
  }
}

uint8_t highscore_get_scores(uint8_t place){
  if(place >= HIGHSCORE_SCORES_NUM) return 0;
  return xmem_read(HIGHSCORE_SRAM_ADDRESS_START + place);
}