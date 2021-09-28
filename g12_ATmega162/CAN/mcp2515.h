/*
 *
 */

#ifndef MCP2515_H
#define MCP2515_H

#include <stdint.h>

unsigned char mcp_read(uint8_t address);

void mcp_write(uint8_t address, uint8_t data);

void mcp_request_to_send(uint8_t registers);

unsigned char mcp_read_status(void);

void mcp_reset(void);

void mcp_bit_manipulation(uint8_t address, uint8_t mask, uint8_t data);

unsigned char mcp_read_rx_buffer(uint8_t address_n, uint8_t address_m);

#endif 