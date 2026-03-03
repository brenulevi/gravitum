#pragma once

#include <stdint.h>
#include <stddef.h>

#include "stm32f4xx_hal.h"

typedef struct I2C_Controller
{
    I2C_HandleTypeDef* hi2c;
    volatile int is_busy;
    volatile int rx_complete;
    volatile int tx_complete;
} I2C_Controller;

int I2C_Controller_Init(I2C_Controller* controller, I2C_HandleTypeDef* hi2c);

HAL_StatusTypeDef I2C_Controller_BlockingMemWrite(I2C_Controller* controller, uint16_t addr, uint16_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout);
HAL_StatusTypeDef I2C_Controller_BlockingMemRead(I2C_Controller* controller, uint16_t addr, uint16_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout);