/**
 * @file xmem.h
 * @author Steffen Folåsen, Ask Øren, Sivaranjith Sivarasa
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

/**
 * @brief Write to the external memory and check if the returned value is the same. If they differ try again max 3 times 
 * 
 * @param data The data to write
 * @param addr The address to write data to
 * @return uint8_t 0 if the check was the same as the @p data. 0 otherwise
 */
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
