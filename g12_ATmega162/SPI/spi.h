
#ifndef SPI_H_
#define SPI_H_

/**
 * @brief Initializes SPI for the ATmega162, setting the ATmega162 as master. 
 * Enables PIN4 and set as slave select. Also enables MOSI and MISO. 
 * 
 */
void spi_init(void);

/**
 * @brief Sets slave select low, and transmits data to the SPDR register. 
 * It the waits for the data to finnish transmitting (by checking
 * the SPIF register) before setting the setting the slave select high.
 * 
 * @param data data that is to be transmitted.
 */
void spi_transmit(unsigned char data);

/**
 * @brief 
 * 
 */
void spi_interrupt_init(void);

/**
 * @brief Transmits dummy data using @p spi_transmit() and reads out the data
 * from the SPDR register.
 * 
 * @return unsigned char 
 */
unsigned char spi_receive(void);

#endif