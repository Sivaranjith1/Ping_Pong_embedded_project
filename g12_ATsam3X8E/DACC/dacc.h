/**
 * @file dacc.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa 
 * @brief A driver for using the ATSAMS internal DACC. Converting digital values to analog signals
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DACC_H
#define DACC_H
#include <stdint.h>

/**
 * @brief Enable DACC and pins for the dacc output
 * 
 */
void dacc_init();

/**
 * @brief Convert digital data to analog signal on the pin
 * 
 * @param data the value to output on the dacc pin
 */
void dacc_convert(float data);

#endif //DACC_H