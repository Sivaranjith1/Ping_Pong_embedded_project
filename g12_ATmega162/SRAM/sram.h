#ifndef SRAM_H
#define SRAM_H

/**
 * @brief Currently only calls @p sram_reset function
 * 
 */
void sram_init(void);

/**
 * @brief Set all elements in the SRAM to 0xFF resetting the SRAM
 * 
 */
void sram_reset(void);


#endif //SRAM_H