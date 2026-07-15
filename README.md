# Embedded_Device_Drivers_Basic_Protocols
 
This repository contains embedded device drivers developed from scratch for the STM32G0 Series microcontroller using register-level programming without relying on the STM32 HAL libraries.

Device Drivers Implemented
GPIO (General Purpose Input/Output)
GPIO initialization
Input/Output configuration
Alternate Function configuration
Pull-up/Pull-down configuration
GPIO read/write/toggle operations
Interrupt configuration

USART (Universal Synchronous/Asynchronous Receiver Transmitter)
USART initialization
Baud rate configuration
Polling-based transmission and reception
Interrupt-driven transmission and reception

SPI (Serial Peripheral Interface)
SPI initialization
Master mode communication
Full-duplex data transmission and reception
Polling-based driver implementation
Interrupt-driven transmission and reception


I2C (Inter-Integrated Circuit)
I2C peripheral initialization
Master transmit
Master receive
Polling-based communication
Interrupt-driven transmission and reception


Features
Register-level programming
Drivers developed completely from scratch
Modular and reusable driver architecture
Well-structured source and header files
Suitable for learning STM32 peripheral programming and embedded driver development
Target Platform
Microcontroller: STM32G0 Series
Language: C
IDE: STM32CubeIDE
Purpose
The objective of this repository is to understand the internal working of STM32 peripherals by developing reusable peripheral drivers from scratch rather than using vendor-provided libraries. These drivers can serve as a foundation for embedded firmware development and further protocol implementation.
