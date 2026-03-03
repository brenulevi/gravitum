#include "BMP581_Driver.h"
#include "I2C_Controller.h"

int BMP581_Driver_Init(BMP581_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr)
{
    if (driver == NULL || i2c_controller == NULL)
    {
        return -1;
    }

    driver->i2c_controller = i2c_controller;
    driver->addr = addr;
    
    // Read chip ID to verify communication
    uint8_t chip_id;
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, BMP581_REG_CHIP_ID, &chip_id, 1, 100) != 0)
    {
        return -1;
    }

    driver->chip_id = chip_id;

    return 0;
}

int BMP581_Driver_ReadTemperatureAndPressure(BMP581_Driver* driver, float* temperature, float* pressure)
{
    if (driver == NULL)
    {
        return -1;
    }

    uint8_t temp_data[6];
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, BMP581_REG_DATA, temp_data, 6, 100) != 0)
    {
        return -1;
    }

    driver->raw_temperature = (temp_data[2] << 16) | (temp_data[1] << 8) | temp_data[0];
    driver->raw_pressure = (temp_data[5] << 16) | (temp_data[4] << 8) | temp_data[3];

    driver->temperature = driver->raw_temperature >> 16;
    driver->pressure = driver->raw_pressure >> 6;

    *temperature = driver->temperature;
    *pressure = driver->pressure;

    return 0;
}

int BMP581_Driver_SetConfiguration(BMP581_Driver* driver, BMP581_PowerMode power_mode, BMP581_OutputDataRate odr)
{
    if (driver == NULL)
    {
        return -1;
    }

    uint8_t config_data = 0x00 | ((odr << 2) & 0x7C) | (power_mode & 0x03);

    if (I2C_Controller_BlockingMemWrite(driver->i2c_controller, driver->addr, BMP581_REG_ODR, &config_data, 1, 100) != 0) // Assuming config register is at 0x1F
    {
        return -1;
    }

    driver->power_mode = power_mode;
    driver->odr = odr;

    return 0;
}