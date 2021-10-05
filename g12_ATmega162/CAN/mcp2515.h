/*
 *
 */

#ifndef MCP2515_H
#define MCP2515_H

#include <stdint.h>

/**
 * @brief Initialises the MCP by calling @p mcp_reset()
 * 
 * @return uint8_t should be 0 when the initialise function doesn't run into any issues
 */
uint8_t mcp_init(void);

/**
 * @brief Uses @p spi_transmit() to read a given register
 * 
 * @param address of the register to be read
 * @return unsigned char 
 */
unsigned char mcp_read(uint8_t address);

/**
 * @brief Write data to register of the MCP2515 
 * 
 * @param address Address to write to
 * @param data Data to write to the register
 */
void mcp_write(uint8_t address, uint8_t data);

/**
 * @brief Requests transmission of the data saved on the MCP data register
 * 
 * @param registers with data ready for transmission
 */
void mcp_request_to_send(uint8_t registers);

/**
 * @brief Reads the status register
 * 
 * @return unsigned char 
 */
unsigned char mcp_read_status(void);

/**
 * @brief Resets the mcp2515
 * 
 */
void mcp_reset(void);

/**
 * @brief Used to set/clear individual bits of status and control registers. 
 * 
 * @param address of the register to modify individual bits on
 * @param mask decides which bits to modify
 * @param data the values for all bits, although only some of them are changed depending on the mask value
 */
void mcp_bit_manipulation(uint8_t address, uint8_t mask, uint8_t data);

/**
 * @brief Reads a chosen RX buffer
 * 
 * @param address_n decided together with @p address_m which of the two registers will be read
 * as well as whether the read will start at RXBnSIDH or RXBnSIDn
 * @param address_m 
 * @return unsigned char 
 */
unsigned char mcp_read_rx_buffer(uint8_t address_n, uint8_t address_m);


#endif 