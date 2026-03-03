#pragma once

#include <stddef.h>
#include <stdint.h>

#include "I2C_Controller.h"

typedef enum TMP100_Register
{
    TMP100_REG_TEMP = 0x00,
    TMP100_REG_CONFIG = 0x01
} TMP100_Register;

typedef enum TMP100_Resolution
{
    TMP100_RES_9_BIT = 0x0,
    TMP100_RES_10_BIT = 0x1,
    TMP100_RES_11_BIT = 0x2,
    TMP100_RES_12_BIT = 0x3
} TMP100_Resolution;

typedef struct TMP100_Driver
{
    I2C_Controller* i2c_controller;
    uint16_t addr;
    TMP100_Resolution resolution;
    float conversion_factor;
    int16_t raw_temperature;
    float last_temperature;
} TMP100_Driver;

int TMP100_Driver_Init(TMP100_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr);
int TMP100_Driver_ReadTemperature(TMP100_Driver* driver, float* temperature);
int TMP100_Driver_SetResolution(TMP100_Driver* driver, TMP100_Resolution resolution);