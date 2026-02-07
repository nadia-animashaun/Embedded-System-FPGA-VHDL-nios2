# Embedded Firmware (Nios II)

This directory contains embedded C firmware running on a Nios II soft-core
processor. The firmware interfaces directly with hardware components using
memory-mapped I/O.

## Purpose
The firmware demonstrates low-level embedded programming in a bare-metal
environment, enabling control and monitoring of on-chip peripherals.

## Functionality
- Analog input sampling via ADC
- LED control and timer-based operations
- UART communication
- Interrupt and exception handling

## Files
- `main.c` — Firmware entry point and application logic
- `adc.c / adc.h` — ADC driver and interface
- `chario.c / chario.h` — Character I/O and UART support
- `exception_handler.c` — Interrupt and exception handling routines
- `leds.h` — LED control definitions
- `timer.h` — Timer interface definitions
- `nios2_control.h` — Nios II control and register definitions
- `makefile` — Build configuration

## Development Model
- Bare-metal execution (no operating system)
- Register-level hardware access
- Makefile-based build system
