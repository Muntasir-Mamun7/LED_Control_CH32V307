# CH32V307 LED Control via UART Commands
1. Project Overview
This project is an embedded system that allows for the control of an onboard LED on a WCH CH32V307 (RISC-V) development board using commands sent over a UART serial connection from a host computer. It serves as a basic example of GPIO control, UART communication, and command processing on the CH32V307 platform.

The system listens for specific hexadecimal commands to turn the LED on or off and sends a confirmation message back to the host computer.

2. Features
Remote LED Control: Turn an LED on and off by sending commands from a PC.

UART Communication: Utilizes USART1 for robust serial communication.

Simple Command Protocol: Responds to single-byte commands for straightforward operation.

Status Feedback: Provides confirmation messages to the serial terminal upon successful command execution.

Active-Low Logic: Correctly handles the active-low configuration of the onboard LED.

3. Hardware Requirements
CH32V307 Development Board: The target microcontroller board.

USB-to-UART Converter: An onboard or external converter (e.g., using a CH340 chip) to connect the MCU to a PC.

Host PC: A computer to send commands from.

USB Cable: To connect the development board to the PC.

4. Software Requirements
IDE: MounRiver Studio

Compiler: RISC-V Embedded GCC

Serial Terminal Program: A terminal emulator like RealTerm, Tera Term, or PuTTY to interact with the device.

5. Setup and Installation
Hardware Connection: Connect the CH32V307 development board to your PC using a USB cable.

Driver Installation: Ensure that the necessary USB-to-UART drivers (e.g., CH340) are installed on your PC. Your system should recognize the board and assign it a COM port.

Open Project: Launch MounRiver Studio and open the project files.

Build and Flash: Compile the project and flash the generated firmware onto the CH32V307 microcontroller.

6. How to Use
After flashing the firmware, identify the COM port assigned to your CH32V307 board through your operating system's Device Manager.

Open your preferred serial terminal program (e.g., RealTerm).

Configure the terminal connection with the following settings:

Port: The COM port identified in step 1.

Baud Rate: 115200

Data Bits: 8

Parity: None

Stop Bits: 1

Open the serial connection.

Send the hexadecimal commands to control the LED.

7. Command Reference
The system accepts the following single-byte hexadecimal commands:

Command

Value (Hex)

Value (Decimal)

Description

LED ON

0xAA

170

Turns the onboard LED ON.

LED OFF

0xBB

187

Turns the onboard LED OFF.

Upon receiving a valid command, the device will respond with a confirmation message like "LED turned ON" or "LED turned OFF".
