#pragma once

#include <stddef.h>
#include <stdint.h>

#include "I2C_Controller.h"

typedef enum BMP581_Register
{
    BMP581_REG_DATA = 0x1D,
    BMP581_REG_ODR = 0x37,
    BMP581_REG_CHIP_ID = 0x01
} BMP581_Register;

typedef enum BMP581_PowerMode
{
    BMP581_POWER_MODE_STANDBY = 0x00,
    BMP581_POWER_MODE_NORMAL = 0x01
} BMP581_PowerMode;

typedef enum BMP581_OutputDataRate
{
    BMP581_ODR_240_HZ = 0x00,
    BMP581_ODR_120_HZ = 0x01,
    BMP581_ODR_60_HZ = 0x02,
    BMP581_ODR_1_HZ = 0x1C
} BMP581_OutputDataRate;

typedef struct BMP581_Driver
{
    I2C_Controller* i2c_controller;
    uint16_t addr;

    int8_t chip_id;

    BMP581_PowerMode power_mode;
    BMP581_OutputDataRate odr;

    int32_t raw_temperature;
    int32_t raw_pressure;

    float pressure;
    float temperature;
} BMP581_Driver;

int BMP581_Driver_Init(BMP581_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr);
int BMP581_Driver_ReadTemperatureAndPressure(BMP581_Driver* driver, float* temperature, float* pressure);
int BMP581_Driver_SetConfiguration(BMP581_Driver* driver, BMP581_PowerMode power_mode, BMP581_OutputDataRate odr);