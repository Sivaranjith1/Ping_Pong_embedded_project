#include "can.h"
#include "mcp2515.h"
#include "mcp_constants.h"
#include <avr/io.h>

void can_init(void){
    mcp_write(MCP_CNF1, (1 << 7) | 1);
    mcp_write(MCP_CNF3, 3);
    mcp_write(MCP_CNF2, (1 << 7) | (3 << 2) | (1 << 1));
    mcp_bit_manipulation(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // setting CAN to normal mode

    mcp_write(MCP_TXRTSCTRL, 0b000); //Sets TXnRTS pins to digital inputs

    mcp_write(MCP_CANINTE, 1 << 2); //Enables CAN interrupt to TXB0
    mcp_write(MCP_CANINTE, MCP_RX_INT); 
    
    SREG = (0 << 8); // disable global interrupts
    GICR = (1 << INT1) | (1 << INT0) | (1 << INT2); // enable interrupts for pins INT0 - INT2
    MCUCR = (2 << ISC10) | (2 << ISC00); // falling edge interrupt for both INT0 and INT1
    EMCUCR = 1; // External interrupt enable on INT2
    GIFR = (1 << INTF0) | (1 << INTF1) | (1 << INTF2); // clear flags
    SREG = (1 << 8); // enable global interrupts

}

void can_transmit(can_frame_t* can_frame){
    mcp_write(MCP_TXB0SIDH, 0xFF & (can_frame->id >> 3)); // setting higher id fields
    mcp_write(MCP_TXB0SIDL, 0xFF & (can_frame->id << 5)); // setting lower id fields
    mcp_write(MCP_TXB0DLC, (uint8_t)(can_frame->rtr) << 6 | can_frame->data_len); // setting data_len
    for (uint8_t i = 0; i < 8; i++)
    {
        mcp_write(MCP_TXB0D0 + i, can_frame->data[i]);
    }

    mcp_write(MCP_TXB0CTRL, 0x8);    //Set Message transmit request
    mcp_request_to_send(1);
    
}

void can_receive(uint8_t rxb_register, can_frame_t* can_frame){
    uint8_t RXBnSIDH    = 0; //registers for higher id fields
    uint8_t RXBnSIDL    = 0; //registers for lower id fields 
    uint8_t RXBnDLC     = 0; //registers for data len and rtr
    uint8_t RXBnD0      = 0; //first register of data

    switch (rxb_register)
    {
        case 0:
        {
            RXBnSIDH    = MCP_RXB0SIDH;
            RXBnSIDL    = MCP_RXB0SIDL;
            RXBnDLC     = MCP_RXB0DLC;
            RXBnD0      = MCP_RXB0D0;
            break;
        }
        case 1: 
        {   
            RXBnSIDH    = MCP_RXB1SIDH;
            RXBnSIDL    = MCP_RXB1SIDL;
            RXBnDLC     = MCP_RXB1DLC;
            RXBnD0      = MCP_RXB1D0;
            break;
        }
        default:
        {
            break;
        }
    }
    
    can_frame->id = (mcp_read(RXBnSIDH) << 3) | (mcp_read(MCP_RXB0SIDL) >> 5);
    unsigned char rxb = mcp_read(RXBnDLC);
    can_frame->data_len = rxb & (0x0F);
    can_frame->rtr = (rxb & 0x40) >> 6; 
    
    for(uint8_t i = 0; i < can_frame->data_len; i++){
        can_frame->data[i] = mcp_read(RXBnD0 + i);
    }
}