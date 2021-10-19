/**
 * @file can_controller.h
 * @author Gustav O. Often and Eivind H. Jølsgard 
 * @brief Init, send and receive can frames for ATSAM3X8E
 * @note For use in TTK4155 Embedded and Industrial Computer Systems Design
 * @version 0.1
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include <stdint.h>

typedef union {
 char char_array[8];
 float f32[2];
 uint64_t i64;
} can_data_t;

/**
 * @brief Struct for defining a can frame
 * @param id the id of the message. Lower id will be prioritized over higher ids on the can bus
 * @param data_len the length of the can frame, between 1 and 8
 * @param data a array of len 8 with the data. data[0] is the least significant byte
 * 
 */
typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	can_data_t data;
} CAN_MESSAGE;

/**
 * @brief Initialize can bus with predefined number of rx and tx mailboxes, 
 * 
 * @param can_br Value to be set in CAN0->CAN_BR register to match can bus bit timing 
 * @return uint8_t Success(0) or failure(1) 
 */
uint8_t can_init_def_tx_rx_mb(uint32_t can_br);

/**
 * @brief Initialize can bus
 * 
 * @param can_br Value to be set in CAN0->CAN_BR register to match can bus bit timing
 * @param num_tx_mb Number of transmit mailboxes, 	tx mb indexes: [0		, num_tx_mb-1]
 * @param num_rx_mb Number of receive mailboxes, 	rx mb indexes: [num_tx_mb, num_rx_mb-1]
 * @return uint8_t Success(0) or failure(1)
 */
uint8_t can_init(uint32_t can_br, uint8_t num_tx_mb, uint8_t num_rx_mb);

/**
 * @brief Send can message from mailbox
 * 
 * @param can_msg message to be sent
 * @param mailbox_id ID of transmit mailbox to be used
 * @return uint8_t Success(0) or failure(1)
 */
uint8_t can_send(CAN_MESSAGE* can_msg, uint8_t mailbox_id);

/**
 * @brief Read can message from mailbox 
 * 
 * @param can_msg struct instance to save received data 
 * @param mailbox_id ID of receive mailbox to be used
 * @return uint8_t Success(0) or failure(1)
 */
uint8_t can_receive(CAN_MESSAGE* can_msg, uint8_t mailbox_id);

#endif /* CAN_CONTROLLER_H_ */