# Testbench & Verification

This directory contains VHDL testbenches and simulation scripts used to verify
the functionality of the embedded system hardware.

## Purpose
The testbenches validate correct system behavior prior to deployment on FPGA
hardware. Verification focuses on address decoding, memory access, and
hardware–software interaction at the register level.

## Verification Scope
- Address decoding and memory-mapped I/O correctness
- ROM and RAM read/write operations
- Processor interface behavior
- System-level signal integrity

## Files
- `tb_system.vhd` — System-level VHDL testbench
- `system.do` — Simulation script for automated test execution

## Tools
- ModelSim / Questa (VHDL simulation)
