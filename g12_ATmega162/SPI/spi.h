
#ifndef SPI_H_
#define SPI_H_

void spi_init(void);

void spi_transmit(unsigned char data);

void interrupt_init(void);

unsigned char spi_receive(void);

#endif