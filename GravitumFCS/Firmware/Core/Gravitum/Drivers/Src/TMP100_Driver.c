#include "TMP100_Driver.h"
#include "I2C_Controller.h"

int TMP100_Driver_Init(TMP100_Driver* driver, I2C_Controller* i2c_controller, uint16_t addr)
{
    if (driver == NULL || i2c_controller == NULL)
    {
        return -1;
    }

    driver->i2c_controller = i2c_controller;
    driver->addr = addr;
    driver->resolution = TMP100_RES_12_BIT; // Default resolution
    driver->last_temperature = 0.0f;

    // Set default resolution in the sensor
    return TMP100_Driver_SetResolution(driver, driver->resolution);

    return 0;
}

int TMP100_Driver_ReadTemperature(TMP100_Driver* driver, float* temperature)
{
    if (driver == NULL || temperature == NULL)
    {
        return -1;
    }

    uint8_t temp_data[2];
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, TMP100_REG_TEMP, temp_data, 2, 1000) != HAL_OK)
    {
        return -1; // Read failed
    }

    driver->raw_temperature = (temp_data[0] << 8) | temp_data[1];
    driver->raw_temperature >>= 4;

    *temperature = driver->raw_temperature * driver->conversion_factor;
    driver->last_temperature = *temperature;

    return 0;
}

int TMP100_Driver_SetResolution(TMP100_Driver* driver, TMP100_Resolution resolution)
{
    if (driver == NULL)
    {
        return -1;
    }

    switch (resolution)
    {
        case TMP100_RES_9_BIT:
            driver->conversion_factor = 0.5f;
            break;
        case TMP100_RES_10_BIT:
            driver->conversion_factor = 0.25f;
            break;
        case TMP100_RES_11_BIT:
            driver->conversion_factor = 0.125f;
            break;
        case TMP100_RES_12_BIT:
            driver->conversion_factor = 0.0625f;
            break;
        default:
            return -1; // Invalid resolution
    }

    uint8_t config_data;
    if (I2C_Controller_BlockingMemRead(driver->i2c_controller, driver->addr, TMP100_REG_CONFIG, &config_data, 1, 100) != HAL_OK)
    {
        return -1; // Read failed
    }

    config_data &= ~(0x03 << 5); // Clear resolution bits (bits 5 and 6)
    config_data |= (resolution << 5); // Set new resolution

    if (I2C_Controller_BlockingMemWrite(driver->i2c_controller, driver->addr, TMP100_REG_CONFIG, &config_data, 1, 1000) != HAL_OK)
    {
        return -1; // Write failed
    }

    driver->resolution = resolution;

    return 0;
}