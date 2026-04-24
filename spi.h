/*
 * spi.h
 *
 *  Created on: 2 Nov 2025
 *      Author: IDGAF
 */

#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>
void SPI_Init(void);
void SPI_Transmit(uint8_t* buffer, uint8_t length);


#endif /* SPI_H_ */
