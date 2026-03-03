#pragma once

#include <stddef.h>
#include <stdint.h>

#include "I2C_Controller.h"

typedef enum IIS2MDC_Register
{
    IIS2MDC_REG_WHO_AM_I = 0x4F,
    IIS2MDC_REG_CFG_REG_A = 0x60,
    IIS2MDC_REG_CFG_REG_B = 0x61,
    IIS2MDC_REG_CFG_REG_C = 0x62,
    IIS2MDC_REG_DATA = 0x68
} IIS2MDC_Register;

typedef enum IIS2MDC_OperationMode
{
    IIS2MDC_MODE_CONTINUOUS = 0x0,
    IIS2MDC_MODE_SINGLE = 0x1,
} IIS2MDC_OperationMode;

typedef enum IIS2MDC_OutputDataRate
{
    IIS2MDC_ODR_10Hz = 0x0,
    IIS2MDC_ODR_20Hz = 0x1,
    IIS2MDC_ODR_50Hz = 0x2,
    IIS2MDC_ODR_100Hz = 0x3,
} IIS2MDC_OutputDataRate;

typedef enum IIS2MDC_CompensationMode
{
    IIS2MDC_COMPENSATION_OFF = 0x0,
    IIS2MDC_COMPENSATION_ON = 0x1,
} IIS2MDC_CompensationMode;

typedef struct IIS2MDC_Driver
{
    I2C_Controller* i2c_controller;
    uint16_t addr;

    IIS2MDC_OperationMode operation_mode;
    IIS2MDC_OutputDataRate output_data_rate;
    IIS2MDC_CompensationMode compensation_mode;

    uint8_t chip_id;

    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;
    int16_t raw_temperature;

    float mag[3];
    float temperature;
} IIS2MDC_Driver;

int IIS2MDC_Driver_Init(IIS2MDC_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr);
int IIS2MDC_Driver_ReadMagnetometerAndTemperature(IIS2MDC_Driver* driver, float mag[3], float* temperature);
int IIS2MDC_Driver_SetConfiguration(IIS2MDC_Driver* driver, IIS2MDC_OperationMode operation_mode, IIS2MDC_OutputDataRate output_data_rate, IIS2MDC_CompensationMode compensation_mode);