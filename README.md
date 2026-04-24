# SPI LED Bar Graph Control using EFM8

## Description
This project implements SPI (Serial Peripheral Interface) communication between the EFM8BB52 microcontroller and a 10-LED Bar Graph module.

The system controls LED patterns using shift registers and demonstrates embedded firmware design with modular code structure.

---

## Features
- SPI communication between EFM8BB52 and LED Bar Graph module
- Control of 10 LEDs using shift registers (74HC595)
- Implementation of dynamic LED patterns:
  - Heartbeat pattern
  - Bouncing light pattern
- Modular firmware design (separate SPI, control, and main logic)

---

## Hardware & Tools
- Microcontroller: EFM8BB52
- LED Module: 10-LED Bar Graph Click
- Shift Register: 74HC595
- IDE: Simplicity Studio 5
- Programming Language: C
- Communication Protocol: SPI

---

## Project Structure
spi-led-bargraph-efm8/
│
├── src/
│ ├── main.c
│ ├── spi.c
│ ├── bar_control.c
│
├── include/
│ ├── spi.h
│ ├── main.h
│
├── docs/
│ └── report.pdf



---

## Working Principle
- The EFM8 microcontroller acts as SPI master.
- Data is transmitted via MOSI to the shift register.
- The 74HC595 converts serial data into parallel LED outputs.
- LEDs update when the Chip Select (CS) signal is triggered.
- LED patterns are generated using bit shifting.

---

## Results
- Heartbeat LED pattern (center expanding)
- Bouncing LED pattern (left to right movement)

These confirm correct SPI communication and LED control.

---

## Learning Outcomes
- Understanding SPI protocol (Mode 0)
- Working with shift registers (74HC595)
- Embedded C programming
- Modular firmware design

---

## Author
Kulsang Thupten Sherpa  
Electrical Engineering Student (RWU, Germany)
