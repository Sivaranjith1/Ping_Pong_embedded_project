/**
 * @file system_config.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Global configuration for the ATSAME3X8E
 * @version 1.0
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

/**
 * @brief 
 * 
 */
//                         BRP     SJW      ProPag   Phase 1  Phase 2
#define CAN_BR_VALUES (20 << 16 | 2 << 12 | 2 << 8 | 2 << 4 | 3)

/**
 * @brief Debug control for ATsam
 * 
 */

#define CAN_DEBUG 0
#define CAN_DEBUG_BUTTON 0
#define TC0_DEBUG 0
#define TC1_DEBUG 0
#define TC2_DEBUG 0
#define DACC_DEBUG 0
#define DEBUG_INTERRUPT 0
#define ADC_DEBUG 0
#define PID_DEBUG 0
#define JOYSTICK_DEBUG 0
#define EEFC_DEBUG 0

#endif /* SYSTEM_CONFIG_H_ */
