/**
 * @file eefc.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Driver for the use of flash memory, includes both reading and writing functionality
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef EEFC_H
#define EEFC_H

#include <stdint.h>

#define FLASH_PAGE_JOYSTICK_CALIBRATION 50

/**
 * @brief Initialises both EFC0 and EFC1 with FWS = 6
 * As per 49.1.1.1
 */
void eefc_init(void);

 /**
  * @brief Reads the content of a single page
  * following the steps described in 49.1.1.2
  * @param page_number page to be read
  * @return uint32_t* array with 8 * 32 bits of data
  */
uint32_t *eefc_read_single_page(uint16_t page_number);

/**
 * @brief Writes a set of data into a specific page number.
 * This function also erases previous data found in said page.
 * 
 * @param page_number page number to be erased and written to.
 * @param data to be written.
 */
void eefc_write_page(uint16_t page_number, uint32_t* data);

/**
 * @brief Fetches and prints the flash descriptor by passing
 * GETD to the EFC control register.
 */
void eefc_read_flash_descriptor(void);

#endif //EEFC_H
