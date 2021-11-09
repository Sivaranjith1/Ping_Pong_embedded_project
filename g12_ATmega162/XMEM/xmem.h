/**
 * @file xmem.h
 * @author Steffen Folåsen
 * @brief Library for interfacing with AVR's external memory, xmem
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdint.h>

#ifndef XMEM_H_
#define XMEM_H_

/**
 * @brief Enable AVR interface for external memory (xmem)
 * 
 */
void xmem_init(void);

/**
 * @brief Write to the external memory
 * 
 * @param data byte of data to write
 * @param addr Adress of external memory for 0x1000. I.e will 0x1800 in absolut result in 0x800 as adress
 */
void xmem_write(uint8_t data, uint16_t addr);

uint8_t xmem_write_with_check(uint8_t data, uint16_t addr);

/**
 * @brief Read a byte from external memory
 * 
 * @param addr Adress of external memory for 0x1000. I.e will 0x1800 in absolut result in 0x800 as adress
 * @return uint8_t The byte of data stored in this memory
 */
uint8_t xmem_read(uint16_t addr);


/**
 * @brief Run a SRAM test. This will loop through every function in the sram memory space and validate that the input and output data is the same
 * 
 */
void xmem_SRAM_test(void);

#endif /* XMEM_H_ */
