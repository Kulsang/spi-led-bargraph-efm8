/*
 * spi.c
 *
 *  Created on: 2 Nov 2025
 *      Author: IDGAF
 */


#include <SI_EFM8BB52_Register_Enums.h>         // SFR declarations

//-----------------------------------------------------------------------------
// SPI
//-----------------------------------------------------------------------------

void SPI_Init(void)
{
    // MSTEN (Master), CKPHA=0, CKPOL=0 (Mode 0)
    SPI0CFG = SPI0CFG_MSTEN__MASTER_ENABLED |
              SPI0CFG_CKPHA__DATA_CENTERED_FIRST |
              SPI0CFG_CKPOL__IDLE_LOW;

    // Set to 3-Wire Master Mode (NSSMD[1:0] = 00).
    SPI0CN0 &= ~(SPI0CN0_NSSMD__FMASK); // Clear the NSSMD bits
    SPI0CN0 |= SPI0CN0_NSSMD__3_WIRE; // Set to 3-wire master

    //   SPI0CKR = 1. SPI_CLK = 3.0625 / 4 = ~765 kHz
    SPI0CKR = 1;

    //  Enable SPI peripheral
    SPI0CN0 |= SPI0CN0_SPIEN__ENABLED;
}

uint8_t SPI_WriteByte(uint8_t tx_byte)
{
    SPI0CN0_SPIF = 0;                  // Clear the SPIF flag
    SPI0DAT = tx_byte;                 // Write the byte to transmit
    while(SPI0CN0_SPIF == 0);          // Wait for the transfer to complete
    return SPI0DAT;                    // Return the byte received
}


void SPI_Transmit(uint8_t* buffer, uint8_t length)
{
    uint8_t i;
    for (i = 0; i < length; i++)
    {
        SPI_WriteByte(buffer[i]);
    }
}
