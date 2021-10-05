#ifndef CAN_H
#define CAN_H

#include <stdint.h>

/**
 * @brief Enum for determining the type of can frame. It can either be a dataframe or a request 
 * 
 */
typedef enum {
    DATA_FRAME = 0,
    REMOTE_TRANSMIT_REQUEST = 1
} can_rtr_t;

/**
 * @brief Struct for defining a can frame
 * @param id the id of the message. Lower id will be prioritized over higher ids on the can bus
 * @param rtr @p can_rtr_t defining if it is a dataframe or a request
 * @param data_len the length of the can frame, between 1 and 8
 * @param data a array of len 8 with the data. data[0] is the least significant byte
 * 
 */
typedef struct {
    uint16_t id;
    can_rtr_t rtr;
    unsigned char data_len;
    unsigned char data[8];
} can_frame_t;

/**
 * @brief Sets CAN to normal mode. Also sets TXnRTS pins to digital inputs and
 * enables CAN interrupt to TXB0.
 * 
 */
void can_init(void);

/**
 * @brief uses @p can_frame_t to define both where to send data, as well as which data should be sent.
 * The data is then subsequently written to the MCP data registers. Once all data has been transmitted
 * @p mcp_request_to_send is called, and the data is sent.
 * 
 * @param can_frame the frame of the data we wish to send
 */
void can_transmit(can_frame_t* can_frame);

/**
 * @brief Read incomming can frames from the given register of the MCP2515
 * 
 * @param rtx_register which of the two MCP2515 buffers to read from
 * @param can_frame a reference to a can struct that will be the received message 
 */
void can_receive(uint8_t rtx_register, can_frame_t* can_frame);

#endif