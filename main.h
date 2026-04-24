/*
 * main.h
 *
 *  Created on: 2 Nov 2025
 *      Author: IDGAF
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_

#include <SI_EFM8BB52_Register_Enums.h>
#include <stdbool.h>
#include "spi.h"
#include "bar_control.h"
//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
// Board LED
#define LED_PORT SFR_P1
#define LED_PIN  4
SI_SBIT(LED, LED_PORT, LED_PIN);

// SPI Chip Select (CS) Pin for BarGraph
#define CS_PORT SFR_P1
#define CS_PIN  3
SI_SBIT(CS, CS_PORT, CS_PIN);

// Define LED states
#define LED_ON  0
#define LED_OFF 1

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Port_Init(void);
void Timer3_Init(void);
void Delay_ms(uint16_t ms);

#endif /* INCLUDES_MAIN_H_ */
