/**
 * @file can_interrupt.h
 * @author Gustav O. Often and Eivind H. Jølsgard
 * @brief Interrupt function when receiving CAN messages on CAN0.
 * @note For use in TTK4155 Embedded and Industrial Computer Systems Design 
 * NTNU - Norwegian University of Science and Technology
 * @version 0.1
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_

/**
 * @brief Interrupt function when receiving CAN messages on CAN0.
 */
void CAN0_Handler(void);

#endif /* CAN_INTERRUPT_H_ */