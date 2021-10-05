#include "can.h"
#include "mcp2515.h"
#include "mcp_constants.h"

/*
#define TXB0CTRL 0x30
#define TXB1CTRL 0x40
#define TXB2CTRL 0x50
#define BFPCYRL 0x0C
#define TXRTSCTRL 0x0D
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0SIDL 0x32
#define TXB0DLC  0x35
#define TXB0D0   0x36


#define CANSTAT 0x0E
#define CANCTRL 0x0F
#define CANINTE 0x2B
*/

void can_init(void){
    mcp_bit_manipulation(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // setting CAN to loopback mode
    mcp_write(MCP_CNF1, 1);
    mcp_write(MCP_CNF3, 1);
    mcp_write(MCP_CNF2, (1 << 7) | (1 << 6) | (1 << 3) | 1);
    mcp_write(MCP_TXRTSCTRL, 0b000); //Sets TXnRTS pins to digital inputs
    mcp_write(MCP_CANINTE, 1 << 2); //Enables CAN interrupt to TXB0
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
