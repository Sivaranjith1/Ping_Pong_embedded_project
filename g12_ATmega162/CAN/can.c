#include "can.h"
#include "mcp2515.h"

//#define CAN ((CAN_REGS*))

/*
struct CAN_REGS{
    volatile uint8_t BFPCYRL;
    volatile uint8_t TXRTSCTRL;
    volatile uint8_t CANSTAT;
    volatile uint8_t CANCTRL;
};
*/

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


void can_init(void){
    mcp_bit_manipulation(CANCTRL, 0xFF, 0b010 << 5);
    mcp_write(TXRTSCTRL, 0b000);
    mcp_write(CANINTE, 1 << 2);
}

void can_transmit(can_frame_t* can_frame){
    mcp_write(TXB0SIDH, 0xFF & (can_frame->id >> 3)); // setting higher id fields
    mcp_write(TXB0SIDL, 0xFF & (can_frame->id << 5)); // setting lower id fields
    mcp_write(TXB0DLC, (uint8_t)(can_frame->rtr) << 6 | can_frame->data_len); // setting data_len
    for (uint8_t i = 0; i < 8; i++)
    {
        mcp_write(TXB0D0 + i, can_frame->data[i]);
    }

    mcp_write(TXB0CTRL, 0x8);    //Set Message transmit request
    mcp_request_to_send(1);
    
}

//void can_
