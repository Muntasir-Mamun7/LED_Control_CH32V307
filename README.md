# CH32V307 LED Control via UART Commands

A simple implementation of LED control using UART commands on CH32V307 microcontroller.

## Project Overview
This project fulfills Task 2 requirements by controlling an onboard LED through UART commands:
- Command 0xAA turns ON the LED
- Command 0xBB turns OFF the LED

## Hardware Requirements
- CH32V307 development board
- USB-to-UART cable or onboard interface
- Terminal software (Tera Term, PuTTY, etc.)

## Software Requirements
- MounRiver Studio IDE
- RISC-V GCC Toolchain
- Serial Terminal (115200 baud, 8N1)

## How to Build and Flash
1. Open project in MounRiver Studio
2. Build using the build button or F7
3. Connect board via USB
4. Flash using the download button

## Testing Instructions
Refer to the User Manual in the docs folder for detailed testing instructions.
