/*
 * IncFile1.h
 *
 * Created: 07.09.2021 12:47:38
 *  Author: sivarans
 */ 
#include <stdint.h>

#ifndef XMEM_H_
#define XMEM_H_

void xmem_init(void);

void xmem_write(uint8_t data, uint16_t adress);

uint8_t xmem_read(uint16_t addr);



#endif /* XMEM_H_ */