#include "main.h"


void SiLabs_Startup (void)
{
    // Disable interrupts globally
    IE_EA = 0;
    // Disable the Watchdog Timer
    WDTCN = 0xDE;
    WDTCN = 0xAD;
    Port_Init();
    Timer3_Init();
    SPI_Init();
    // Enable the Crossbar
    XBR2 = XBR2_XBARE__ENABLED;
    // Re-enable interrupts
    IE_EA = 1;
}

//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
/**
 * @brief
 *
 * LED:    P1.4 (GPIO)
 * CS:     P1.3 (GPIO)
 * SCK:    P1.0 (SPI)
 * MISO:   P1.1 (SPI)
 * MOSI:   P1.2 (SPI)
 */
void Port_Init(void)
{

    // SPI (priority 2) needs P1.0 (SCK), P1.1 (MISO), P1.2 (MOSI)
    // skip all of P0 to force SPI onto P1.
    P0SKIP = 0xFF;

    // On P1, we skip P1.3 (CS), P1.4 (LED).
    P1SKIP = (1 << 3) | (1 << 4); // Skip P1.3, P1.4

    // --- Pin I/O Mode Configuration ---

    // Configure LED (P1.4) and CS (P1.3) as push-pull outputs
    P1MDIN  |= (1 << 4) | (1 << 3);     // P1.4, P1.3 are digital
    P1MDOUT |= (1 << 4) | (1 << 3);     // P1.4, P1.3 are push-pull
    CS = 1;                             // Set CS high (inactive)

    // Configure SPI Pins (P1.0, P1.1, P1.2)
    P1MDIN  |= (1 << 0) | (1 << 1) | (1 << 2); // Set P1.0, P1.1, P1.2 as digital
    P1MDOUT |= (1 << 0) | (1 << 2);           // P1.0 (SCK) & P1.2 (MOSI) are push-pull
    P1MDOUT &= ~(1 << 1);                     // P1.1 (MISO) is open-drain (input)

    // Enable SPI0
    XBR0 = XBR0_SPI0E__ENABLED;
    XBR1 = XBR1_PCA0ME__DISABLED;
}

void Delay_ms(uint16_t ms)
{
    uint16_t i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 300; j++)
        {
           _nop_();
        }
    }
}

void Timer3_Init(void)
{

    if ((LFO0CN & LFO0CN_OSCLEN__BMASK) == 0)
    {
      LFO0CN |= LFO0CN_OSCLEN__ENABLED;
      while ((LFO0CN & LFO0CN_LFORDY__BMASK) == 0);
    }

    // Set Timer 3 to 16-bit auto-reload mode (clear T3SPLIT bit)
    TMR3CN0 &= ~TMR3CN0_T3SPLIT__BMASK;
    TMR3CN0 |= TMR3CN0_T3XCLK__LFOSC_DIV_8;

    //  Set the reload value for 1s (10000 counts)
    //    LFOSC = 80kHz. Clock = 80kHz / 8 = 10kHz.
    //    10000 counts = 1s.
    //    Reload value = 65536 - 10000 = 55536 (0xD8F0)
    TMR3RLL = 0xF0;
    TMR3RLH = 0xD8;
    //load value
    TMR3L = 0xF0;
    TMR3H = 0xD8;

    // Enable the Timer 3 interrupt
    EIE1 |= EIE1_ET3__ENABLED;

    // Start Timer 3
    TMR3CN0 |= TMR3CN0_TR3__BMASK;
}

SI_INTERRUPT(TIMER3_ISR, TIMER3_IRQn)
{
    TMR3CN0 &= ~TMR3CN0_TF3H__BMASK;
    // Toggle LED
    LED = !LED;
}

int main (void)
{
    // Set the mask for LED 1.
    // 0x0001 is binary 0b0000000000000001
    // This is the pattern for just the first LED.

  uint16_t heartbeat_patterns[] = {
          0x0000, //All OFF (Pause)
          0x0030, // 0b000000110000 -> LEDs 5 & 6 ON (Center)
          0x0048, // 0b000001001000 -> LEDs 4 & 7 ON
          0x0084, // 0b000010000100 -> LEDs 3 & 8 ON
          0x0102, // 0b000100000010 -> LEDs 2 & 9 ON
          0x0201, // 0b001000000001 -> LEDs 1 & 10 ON (Peak)
          0x0102, // 0b000100000010 -> Back to LEDs 2 & 9
          0x0084, // 0b000010000100 -> Back to LEDs 3 & 8
          0x0048, // 0b000001001000 -> Back to LEDs 4 & 7
          0x0030, // 0b000000110000 -> Back to LEDs 5 & 6
          0x0000  // All OFF (Pause)
      };
  uint8_t i;

  while (1)
  {
      for(i = 0; i < sizeof(heartbeat_patterns)/sizeof(heartbeat_patterns[0]); i++)
      {
          Set_BarGraph_LEDs(heartbeat_patterns[i]);
          Delay_ms(200); // Adjust speed for heartbeat rhythm
      }
  }
}

