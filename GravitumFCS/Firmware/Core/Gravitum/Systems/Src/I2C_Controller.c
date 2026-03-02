#include "I2C_Controller.h"

int I2C_Controller_Init(I2C_Controller *controller, I2C_HandleTypeDef *hi2c, uint32_t timeout_ms)
{
    if (controller == NULL || hi2c == NULL)
    {
        return -1; /* Error: Invalid parameters */
    }

    controller->hi2c = hi2c;
    controller->timeout_ms = timeout_ms;
    
    return 0; /* Success */
}

int I2C_Controller_Read(I2C_Controller *controller, uint8_t slave_addr, 
                        uint8_t reg_addr, uint8_t *data, uint16_t length)
{
    if (controller == NULL || controller->hi2c == NULL || data == NULL)
    {
        return -1; /* Error: Invalid parameters */
    }

    /* Convert 7-bit address to 8-bit format (shift left by 1) */
    uint8_t addr_8bit = slave_addr << 1;

    /* Step 1: Write register address */
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(controller->hi2c, addr_8bit, 
                                                        &reg_addr, 1, controller->timeout_ms);
    if (status != HAL_OK)
    {
        return -1; /* I2C transmit failed */
    }

    /* Step 2: Read data from register */
    status = HAL_I2C_Master_Receive(controller->hi2c, addr_8bit, 
                                    data, length, controller->timeout_ms);
    if (status != HAL_OK)
    {
        return -1; /* I2C receive failed */
    }

    return 0; /* Success */
}

int I2C_Controller_Write(I2C_Controller *controller, uint8_t slave_addr,
                         uint8_t reg_addr, uint8_t *data, uint16_t length)
{
    if (controller == NULL || controller->hi2c == NULL || data == NULL)
    {
        return -1; /* Error: Invalid parameters */
    }

    /* Convert 7-bit address to 8-bit format (shift left by 1) */
    uint8_t addr_8bit = slave_addr << 1;

    /* Prepare buffer: [register_addr | data[0] | data[1] | ... ] */
    uint8_t buffer[256];  /* Max 256 bytes (reg + 255 bytes data) */
    
    if (length > 255)
    {
        return -1; /* Error: Data too large */
    }

    buffer[0] = reg_addr;
    for (uint16_t i = 0; i < length; i++)
    {
        buffer[i + 1] = data[i];
    }

    /* Write register address + data in one transaction */
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(controller->hi2c, addr_8bit,
                                                        buffer, length + 1, controller->timeout_ms);
    if (status != HAL_OK)
    {
        return -1; /* I2C transmit failed */
    }

    return 0; /* Success */
}
