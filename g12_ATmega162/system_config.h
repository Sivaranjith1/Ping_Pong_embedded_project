/**
 * @file system_config.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Global configuration for the ATMEGA
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#define F_CPU 4915200UL //The oscillator clock

#define MAX233_BAUDRATE 9600

/**
 * @brief Memory addresses
 * 
 */
#define BASE_ADRESS 0x1000
#define ADC_BASE_ADDRESS 0x400
#define OLED_BASE_ADDRESS_DATA 0x200
#define OLED_BASE_ADDRESS_COMMAND 0x000
#define SRAM_BASE_ADDRESS 0x800
#define OLED_SRAM_ADDRESS_START 0x800
#define OLED_SRAM_ADDRESS_END 0x1000

/**
 * @brief All debug modes
 * 
 */
#define TIMER1_DEBUG 0
#define ADC_DEBUG 0


#endif /* SYSTEM_CONFIG_H_ */
