/*
 * bar_control.c
 *
 *  Created on: 2 Nov 2025
 *      Author: IDGAF
 */
#include "spi.h"
#include <stdint.h>
#include "main.h"
void Set_BarGraph_LEDs(uint16_t mask)
{
    uint8_t bargraph_data[2];

    // Byte 0 (for LEDs 9-10) = Bits 8 and 9 of the mask
    // We mask with 0x03 (0b00000011) to only use the 2 bits for LEDs 9 & 10.
    bargraph_data[0] = (uint8_t)((mask >> 8) & 0x03);
    // Byte 1 (for LEDs 1-8) = Bits 0-7 of the mask
    bargraph_data[1] = (uint8_t)(mask & 0x00FF);

    CS = 0;
    SPI_Transmit(bargraph_data, 2);
    CS = 1;
}
