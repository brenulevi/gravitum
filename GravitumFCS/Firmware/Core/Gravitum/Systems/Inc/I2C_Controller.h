#pragma once

#include <stdint.h>
#include <stddef.h>
#include "stm32f4xx_hal.h"

/**
 * @brief I2C Controller abstraction for managing I2C1 bus communication
 * 
 * This controller provides a simple interface for reading/writing data
 * on the I2C bus, abstracting away HAL details from drivers.
 */

typedef struct I2C_Controller
{
    I2C_HandleTypeDef *hi2c;  /* STM32 HAL I2C1 handle */
    uint32_t timeout_ms;       /* I2C operation timeout in milliseconds */
} I2C_Controller;

/**
 * @brief Initialize I2C_Controller
 * @param controller Pointer to I2C_Controller structure
 * @param hi2c Pointer to STM32 HAL I2C_HandleTypeDef (e.g., &hi2c1)
 * @param timeout_ms Timeout in milliseconds for I2C operations (e.g., 100ms)
 * @return 0 on success, -1 on error
 */
int I2C_Controller_Init(I2C_Controller *controller, I2C_HandleTypeDef *hi2c, uint32_t timeout_ms);

/**
 * @brief Read data from I2C slave device
 * @param controller Pointer to I2C_Controller structure
 * @param slave_addr I2C slave address (7-bit address, not shifted)
 * @param reg_addr Register address to read from
 * @param data Pointer to buffer for storing read data
 * @param length Number of bytes to read
 * @return 0 on success, -1 on error
 */
int I2C_Controller_Read(I2C_Controller *controller, uint8_t slave_addr, 
                        uint8_t reg_addr, uint8_t *data, uint16_t length);

/**
 * @brief Write data to I2C slave device
 * @param controller Pointer to I2C_Controller structure
 * @param slave_addr I2C slave address (7-bit address, not shifted)
 * @param reg_addr Register address to write to
 * @param data Pointer to data buffer to write
 * @param length Number of bytes to write
 * @return 0 on success, -1 on error
 */
int I2C_Controller_Write(I2C_Controller *controller, uint8_t slave_addr,
                         uint8_t reg_addr, uint8_t *data, uint16_t length);
