# Gravitum Hardware

## Components

- STM32F407VGT6 MCU
- BMI088 IMU
- BMP581 Barometer
- IIS2MDCTR Magnetometer
- TMP100 Temperature Sensor
- ABM8G-25.000MHz-18-D2Y-T Crystal Oscillator
- W25Q64JVSSIQ Flash Memory
- 24C01BN(XBLW) EEPROM
- MAX-M8Q-0 GNSS
- PCA9685PW,118 PWM Driver
- SIC437 Bulk Regulator
- LD39200PU33R LDO Regulator
- CH340K USB to serial
- INA219AID Power Monitor

## Protocols

- I2C1: TMP100, BMP581, IIS2MDCTR
- I2C2: 24C01BN, PCA9685PW, INA219AID
- I2C3: Extra Connector
- SPI1: BMI088
- SPI2: W25Q64JVSSIQ
- UART1: USB Debugging (CH340K)
- UART2: Radio Control (FS-iA10B)
- UART3: GNSS
- UART4: Extra Connector
- USB_OTG_FS: USB Programming

## Timers

TODO

## Power Supply

- ~12V Battery input -> Board
- 12V -> SIC437 -> PSPMAA0605H-1R0M-ANP -> 5V
- 5V -> LD39200PU33R -> 3.3V