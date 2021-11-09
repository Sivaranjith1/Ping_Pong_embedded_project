#include "can.h"
#include "mcp2515.h"
#include "mcp_constants.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void can_init(void){
    mcp_write(MCP_CNF3, 0x83); // PS2 = 3, SOF enable so that CNF2 and CNF1 can be written to
    mcp_write(MCP_CNF2, 0x92); // PropSeg = 2, PS1 = 2, Enable PS2 from CNF3
    mcp_write(MCP_CNF1, 0x41); // SJW = 2, BRP = 1
    mcp_bit_manipulation(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // setting CAN to normal mode

    mcp_write(MCP_TXRTSCTRL, 0b000); //Sets TXnRTS pins to digital inputs

    mcp_write(MCP_CANINTE, 1 << 2); //Enables CAN interrupt to TXB0
    mcp_write(MCP_CANINTE, MCP_RX_INT); 
}

void can_transmit(can_frame_t* can_frame){
    static uint8_t can_buffer = 1; //which of the three buffers on the mcp to use
    uint8_t buffer_address = 16*can_buffer; //each registor is 16 places apart
    mcp_write(MCP_TXB0SIDH + buffer_address, 0xFF & (can_frame->id >> 3)); // setting higher id fields
    mcp_write(MCP_TXB0SIDL + buffer_address, 0xFF & (can_frame->id << 5)); // setting lower id fields
    mcp_write(MCP_TXB0DLC  + buffer_address, (uint8_t)(can_frame->rtr) << 6 | can_frame->data_len); // setting data_len
    for (uint8_t i = 0; i < 8; i++)
    {
        mcp_write(MCP_TXB0D0 + i + buffer_address, can_frame->data.char_array[i]);
    }

    mcp_write(MCP_TXB0CTRL + buffer_address, 0x8);    //Set Message transmit request
    mcp_request_to_send(can_buffer);
    
    if(++can_buffer >= 3) can_buffer = 0;
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
        can_frame->data.char_array[i] = mcp_read(RXBnD0 + i);
    }
}

ISR(INT1_vect){
    printf("Hello from INT1\n\r");
    GIFR = (1 << INTF1);
}