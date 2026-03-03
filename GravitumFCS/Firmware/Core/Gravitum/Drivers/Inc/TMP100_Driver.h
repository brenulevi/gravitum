#pragma once

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "I2C_Controller.h"

static const uint8_t TMP100_REG_ADDR_TEMP = 0x00;
static const uint8_t TMP100_REG_ADDR_CONFIG = 0x01;

typedef enum TMP100_Resolution {
  TMP100_RES_9_BIT = 0x00,
  TMP100_RES_10_BIT = 0x01,
  TMP100_RES_11_BIT = 0x02,
  TMP100_RES_12_BIT = 0x03,
  TMP100_RES_INVALID = 0xFF
} TMP100_Resolution;

/* TMP100 Driver Structure */
typedef struct TMP100_Driver {
  uint8_t i2c_address;     /* I2C Slave Address (0x48-0x4F) */
  I2C_Controller *i2c_bus; /* Pointer to I2C_Controller instance */
  TMP100_Resolution resolution; /* Current resolution setting */
  float resolution_factor; /* Temperature resolution factor based on config */
} TMP100_Driver;

/**
 * @brief Initialize TMP100 sensor
 * @param driver Pointer to TMP100_Driver structure
 * @param i2c_bus Pointer to initialized I2C_Controller
 * @param i2c_address I2C slave address of the sensor
 * @return 0 on success, -1 on error
 */
int TMP100_Driver_Init(TMP100_Driver *driver, I2C_Controller *i2c_bus,
                       uint8_t i2c_address);

/**
 * @brief Read temperature from TMP100
 * @param driver Pointer to TMP100_Driver structure
 * @param temp Pointer to store temperature in Celsius
 * @return 0 on success, -1 on error
 */
int TMP100_Driver_ReadTemp(TMP100_Driver *driver, float *temp);

/**
 * @brief Set TMP100 resolution
 * @param driver Pointer to TMP100_Driver structure
 * @param bits Resolution in bits (8, 9, 10, or 12)
 * @return 0 on success, -1 on error
 */
int TMP100_Driver_SetResolution(TMP100_Driver *driver, TMP100_Resolution bits);

/**
 * @brief Get current TMP100 resolution
 * @param driver Pointer to TMP100_Driver structure
 * @return Current resolution setting (TMP100_Resolution enum value)
 */
TMP100_Resolution TMP100_Driver_GetResolution(TMP100_Driver *driver);