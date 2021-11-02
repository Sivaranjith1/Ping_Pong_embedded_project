/**
 * @file uart.h
 * @author Gustav O. Often, Eivind H. Jålsgard
 * @brief A simple interface for receiving and transmitting characters to a computer using UART via the on board USB-connector
 * @version 2.0
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#define UART_RINGBUFFER_SIZE 64

/**
 * @brief Ringbuffer for receiving characters from  
 */
typedef struct uart_ringbuffer_t
{
	uint8_t head, tail;
	char data[UART_RINGBUFFER_SIZE];
} uart_ringbuffer;

/**
 * @brief Configure the uart device and the ringbuffer 
 * 
 */
void configure_uart(void);

/**
 * @brief Gets a character from the uart input
 * 
 * @param c location of character 
 * @return int Success(0) or failure(1)
 */
int uart_getchar(uint8_t *c);

/**
 * @brief Sends a character through the UART interface
 * 
 * @param c Character to be sent
 * @return int Success(0) or failure(1).
 */
int uart_putchar(const uint8_t c);

/**
 * @brief Interrupt handler for the UART interface 
 * 
 */
void UART_Handler(void);


#endif /* UART_H_ */