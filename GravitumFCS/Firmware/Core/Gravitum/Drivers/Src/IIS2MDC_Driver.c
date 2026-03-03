#include "IIS2MDC_Driver.h"

int IIS2MDC_Driver_Init(IIS2MDC_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr)
{
    if (driver == NULL || i2c_controller == NULL)
        return -1;

    driver->i2c_controller = i2c_controller;
    driver->addr = addr;

    //1. Write CFG_REG_A = 80h // Enable temperature compensation
    //2. Write CFG_REG_C = 01h // Mag data-ready interrupt enable
    IIS2MDC_Driver_SetConfiguration(driver, IIS2MDC_MODE_CONTINUOUS, IIS2MDC_ODR_100Hz, IIS2MDC_COMPENSATION_ON);

    // Read chip ID to verify communication
    uint8_t chip_id;
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, IIS2MDC_REG_WHO_AM_I, &chip_id, 1, 100) != 0)
    {
        return -1;
    }

    driver->chip_id = chip_id;

    return 0;
}

int IIS2MDC_Driver_ReadMagnetometerAndTemperature(IIS2MDC_Driver* driver, float mag[3], float* temperature)
{
    if (driver == NULL)
        return -1;

    uint8_t mag_data[8];
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, IIS2MDC_REG_DATA, mag_data, 8, 100) != 0)
    {
        return -1;
    }

    int16_t raw_x = (mag_data[1] << 8) | mag_data[0];
    int16_t raw_y = (mag_data[3] << 8) | mag_data[2];
    int16_t raw_z = (mag_data[5] << 8) | mag_data[4];

    int16_t raw_temp = (mag_data[7] << 8) | mag_data[6];
    driver->raw_temperature = raw_temp >> 4; // Temperature is 12-bit, so shift right by 4

    driver->temperature = driver->raw_temperature / 8.0f;

    // Convert raw values to microteslas (assuming default sensitivity)
    mag[0] = raw_x * 0.15f; // X-axis
    mag[1] = raw_y * 0.15f; // Y-axis
    mag[2] = raw_z * 0.15f; // Z-axis

    return 0;
}