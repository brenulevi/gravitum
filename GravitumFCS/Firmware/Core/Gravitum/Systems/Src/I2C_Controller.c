#include "I2C_Controller.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdint.h>

static I2C_Controller* i2c_controllers[3] = {NULL, NULL, NULL}; // Assuming 3 I2C peripherals

int I2C_Controller_Init(I2C_Controller* controller, I2C_HandleTypeDef* hi2c)
{
    if (controller == NULL || hi2c == NULL)
    {
        return -1;
    }
    controller->hi2c = hi2c;
    controller->is_busy = 0;

    if (hi2c->Instance == I2C1)
        i2c_controllers[0] = controller;
    else if (hi2c->Instance == I2C2)
        i2c_controllers[1] = controller;
    else if (hi2c->Instance == I2C3)
        i2c_controllers[2] = controller;

    return 0; // Success
}

HAL_StatusTypeDef I2C_Controller_BlockingMemWrite(I2C_Controller* controller, uint16_t addr, uint16_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout)
{
    if (controller == NULL || data == NULL)
    {
        return HAL_ERROR;
    }

    if (controller->is_busy)
    {
        return HAL_BUSY;
    }

    controller->is_busy = 1;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(controller->hi2c, addr << 1, mem_addr, I2C_MEMADD_SIZE_8BIT, data, size, timeout);
    controller->is_busy = 0;
    return status;
}

HAL_StatusTypeDef I2C_Controller_BlockingMemRead(I2C_Controller* controller, uint16_t addr, uint16_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout)
{
    if (controller == NULL || data == NULL)
    {
        return HAL_ERROR;
    }

    if (controller->is_busy)
    {
        return HAL_BUSY;
    }

    controller->is_busy = 1;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(controller->hi2c, addr << 1, mem_addr, I2C_MEMADD_SIZE_8BIT, data, size, timeout);
    controller->is_busy = 0;

    return status;
}

HAL_StatusTypeDef I2C_Controller_DMAWrite(I2C_Controller* controller, uint16_t addr, uint8_t* data, uint16_t size)
{
    if (controller == NULL || data == NULL)
    {
        return HAL_ERROR;
    }

    if (controller->is_busy)
    {
        return HAL_BUSY;
    }

    controller->is_busy = 1;
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(controller->hi2c, addr, data, size);

    if (status != HAL_OK)
    {
        controller->is_busy = 0; // Reset busy flag if DMA transfer initiation failed
    }

    return status;
}

HAL_StatusTypeDef I2C_Controller_DMARead(I2C_Controller* controller, uint16_t addr, uint8_t* data, uint16_t size)
{
    if (controller == NULL || data == NULL)
    {
        return HAL_ERROR;
    }

    if (controller->is_busy)
    {
        return HAL_BUSY;
    }

    controller->is_busy = 1;
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive_DMA(controller->hi2c, addr, data, size);

    if (status != HAL_OK)
    {
        controller->is_busy = 0; // Reset busy flag if DMA transfer initiation failed
    }
    return status;
}