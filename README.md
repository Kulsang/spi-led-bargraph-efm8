# SPI LED Bar Graph Control using EFM8BB52

## Project Overview
This project implements SPI (Serial Peripheral Interface) communication between the EFM8BB52 microcontroller and a 10-LED Bar Graph module. The system demonstrates low-level embedded communication, shift register control, and real-time LED pattern generation.

## Description
The EFM8BB52 microcontroller is configured as an SPI master to control a 10-LED bar graph display. Data is transmitted serially to a shift register (74HC595), which converts it into parallel signals to drive the LEDs.

The project focuses on embedded firmware development, including peripheral configuration, timing control, and modular software design.

## Hardware & Tools
- Microcontroller: EFM8BB52 (Silicon Labs)
- LED Module: 10-LED Bar Graph (MikroE Click)
- Shift Register: 74HC595
- IDE: Simplicity Studio 5
- Programming Language: C
- Communication Protocol: SPI (Mode 0)

## Working Principle
- The EFM8BB52 operates as SPI master  
- Data is transmitted via MOSI to the shift register  
- The 74HC595 converts serial data into parallel outputs  
- Chip Select (CS) is manually controlled to latch data  
- LED patterns are generated using bitwise operations and shifting  

## My Contribution
- Configured SPI peripheral (Mode 0) on EFM8BB52  
- Implemented low-level SPI communication in C  
- Controlled Chip Select (CS) manually for data latching  
- Developed LED pattern logic using bit manipulation  
- Structured firmware into modular components (SPI, control, main)  
- Tested and debugged communication using hardware setup  

## Features
- SPI communication between microcontroller and external device  
- Control of 10 LEDs via shift register  
- Heartbeat LED pattern (center expansion)  
- Bouncing light pattern (left-right movement)  
- Modular firmware design for scalability and readability  

## Design Insights
- Correct SPI configuration (clock polarity and phase) is critical  
- Manual control of CS improves synchronization with shift register  
- Bitwise operations allow efficient LED pattern generation  
- Modular code structure simplifies debugging and extension  
- Timing control affects visual smoothness of LED patterns  

## Results
- Successful implementation of SPI communication  
- Stable and repeatable LED pattern generation  
- Accurate control of all 10 LEDs via shift register  

These results confirm correct hardware interfacing and firmware functionality.

## Learning Outcomes
- Practical understanding of SPI protocol and configuration  
- Experience with shift registers (74HC595)  
- Embedded C programming for microcontrollers  
- Peripheral configuration and hardware interfacing  
- Modular firmware design principles  

## Repository Structure
```text
spi-led-bargraph-efm8/
├── src/
│   ├── main.c
│   ├── spi.c
│   ├── bar_control.c
├── include/
│   ├── spi.h
│   ├── main.h
├── docs/
│   └── report.pdf
