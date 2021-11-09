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

#define CAN_DEBUG 1

#endif /* SYSTEM_CONFIG_H_ */
