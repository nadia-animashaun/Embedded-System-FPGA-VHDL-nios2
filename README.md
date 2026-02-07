# Embedded System Design on FPGA (VHDL & Embedded C)

## Overview
This project implements a complete embedded system on FPGA using custom VHDL
hardware modules and embedded C firmware running on a Nios II soft-core processor.
The system demonstrates hardware–software integration, memory-mapped I/O, and
low-level embedded system design.

## System Architecture
The embedded system includes:
- Soft-core processor (Nios II)
- ROM and RAM subsystems
- Address decoding and memory-mapped I/O
- Embedded peripherals (ADC, LEDs, timers, UART)
- Firmware written in embedded C
- VHDL testbenches for verification

## Hardware Layer (VHDL)
The hardware layer is implemented using modular VHDL components that define
the processor interface, memory blocks, address decoder, and system interconnect.
These modules enable structured communication between hardware and firmware
using memory-mapped registers.

## Firmware Layer (Embedded C)
Embedded C firmware runs on the Nios II processor and interfaces directly with
hardware registers to:
- Sample analog inputs via ADC
- Control LEDs and timers
- Handle interrupts and exceptions
- Communicate through UART
The firmware is developed using a bare-metal workflow.

## Verification & Testing
- VHDL testbenches validate correct address decoding and memory behavior
- On-board FPGA testing confirms hardware–software interaction
- Debugging performed at register and bus level

## Tools & Technologies
- VHDL
- Embedded C
- FPGA toolchain (Intel/Altera)
- Nios II processor
- Makefile-based build system

## Skills Demonstrated
- Embedded system architecture
- Hardware verification and debugging
- Memory-mapped I/O
- Hardware–software integration
- Low-level firmware development
