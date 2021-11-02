/**
 * @file sram.h
 * @author Sivaranjith Sivarasa
 * @brief Init and reset the Sram. Interface for reading and writing will be in xmem
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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