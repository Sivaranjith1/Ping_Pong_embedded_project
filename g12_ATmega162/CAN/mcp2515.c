#include "mcp2515.h"
#include "mcp_constants.h"
#include "../SPI/spi.h"
#include <avr/io.h>

unsigned char mcp_read(uint8_t address){
    unsigned char result;
    PORTB &= ~(1 << PIN4);
    spi_transmit(MCP_READ);
    spi_transmit(address);
    result = spi_receive();
    PORTB |= (1 << PIN4);
    return result;
}

void mcp_write(uint8_t address, uint8_t data){
    PORTB &= ~(1 << PIN4);
    spi_transmit(MCP_WRITE);
    spi_transmit(address);
    spi_transmit(data);
    PORTB |= (1 << PIN4);
}

void mcp_request_to_send(uint8_t registers){
    PORTB &= ~(1 << PIN4);
    spi_transmit(registers);
    PORTB |= (1 << PIN4);
}

unsigned char mcp_read_status(void){
    unsigned char result;
    PORTB &= ~(1 << PIN4);
    spi_transmit(MCP_READ_STATUS);
    result = spi_receive();
    PORTB |= (1 << PIN4);
    return result;
}

void mcp_reset(void){
    PORTB &= ~(1 << PIN4);
    spi_transmit(MCP_RESET);
    PORTB |= (1 << PIN4);
}

void mcp_bit_manipulation(uint8_t address, uint8_t mask, uint8_t data){
    PORTB &= ~(1 << PIN4);
    spi_transmit(MCP_BITMOD);
    spi_transmit(address);
    spi_transmit(mask);
    spi_transmit(data);
    PORTB |= (1 << PIN4);
}


unsigned char mcp_read_rx_buffer(uint8_t address_n, uint8_t address_m){
    unsigned char result;
    PORTB &= (1 << PIN4);
    spi_transmit(0b1001000 + (address_n << 2) + (address_m << 1));
    result = spi_receive();
    PORTB |= (1 << PIN4);
    return result;
}

uint8_t mcp_init(void){
    uint8_t retVal;

    mcp_reset (); // Send reset - command

    //// Self - test
    //mcp_read (MCP_CANSTAT ,&retVal );
    //if ((value & MODE_MASK) != MODE_CONFIG) {
    //    printf ("MCP2515 is NOT in configuration mode after reset!\n");
    //    return 1;
    //}
    


    return retVal;
}

