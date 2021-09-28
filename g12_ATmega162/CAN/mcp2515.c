#include "mcp2515.h"
#include "mcp_constants.h"
#include "../SPI/spi.h"

unsigned char mcp_read(uint8_t address){
    spi_transmit(MCP_READ);
    spi_transmit(address);
    return spi_receive();
}

void mcp_write(uint8_t address, uint8_t data){
    spi_transmit(MCP_WRITE);
    spi_transmit(address);
    spi_transmit(data);
}

void mcp_request_to_send(uint8_t registers){
    spi_transmit(registers);
}

unsigned char mcp_read_status(void){
    spi_transmit(MCP_READ_STATUS);
    return spi_receive();
}

void mcp_reset(void){
    spi_transmit(MCP_RESET);
}

void mcp_bit_manipulation(uint8_t address, uint8_t mask, uint8_t data){
    spi_transmit(MCP_BITMOD);
    spi_transmit(address);
    spi_transmit(mask);
    spi_transmit(data);
}


unsigned char mcp_read_rx_buffer(uint8_t address_n, uint8_t address_m){
    spi_transmit(0b1001000 + (address_n << 2) + (address_m << 1));
    return spi_receive();
}



