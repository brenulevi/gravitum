#pragma once

#include <stddef.h>
#include <stdint.h>

#include "I2C_Controller.h"

static const uint8_t BMP581_REG_ADDR_TEMP = 0x1D;
static const uint8_t BMP581_REG_ADDR_PRESSURE = 0x20;
static const uint8_t BMP581_REG_ADDR_ODR = 0x37;

typedef enum BMP581_OutputDataRate {
  BMP581_ODR_240_HZ = 0x0,
  BMP581_ODR_120_HZ = 0x8,
  BMP581_ODR_60_HZ = 0xE,
  BMP581_ODR_1_HZ = 0x1C,
  BMP581_ODR_INVALID = 0xFF
} BMP581_OutputDataRate;

typedef enum BMP581_PowerMode {
  BMP581_PM_STBY = 0x00,
  BMP581_PM_NORMAL = 0x01,
  BMP581_PM_INVALID = 0xFF
} BMP581_PowerMode;

typedef struct BMP581_Driver {
  uint8_t i2c_address;         /* I2C Slave Address (0x76 or 0x77) */
  I2C_Controller *i2c_bus;     /* Pointer to I2C_Controller instance */
  BMP581_OutputDataRate odr;   /* Current Output Data Rate setting */
  BMP581_PowerMode power_mode; /* Current Power Mode setting */
} BMP581_Driver;

/**
 * @brief Initialize BMP581 sensor
 * @param driver Pointer to BMP581_Driver structure
 * @param i2c_bus Pointer to initialized I2C_Controller
 * @param i2c_address I2C slave address of the sensor
 * @return 0 on success, -1 on error
 */
int BMP581_Driver_Init(BMP581_Driver *driver, I2C_Controller *i2c_bus,
                       uint8_t i2c_address);

/**
 * @brief Read temperature and pressure from BMP581
 * @param driver Pointer to BMP581_Driver structure
 * @param temp Pointer to store temperature in Celsius
 * @param pressure Pointer to store pressure in hPa
 * @return 0 on success, -1 on error
 */
int BMP581_Driver_ReadTempAndPressure(BMP581_Driver *driver, float *temp,
                                      float *pressure);

/**
 * @brief Set BMP581 Output Data Rate and Power Mode
 * @param driver Pointer to BMP581_Driver structure
 * @param odr Desired Output Data Rate (BMP581_OutputDataRate enum)
 * @param pwr_mode Desired Power Mode (BMP581_PowerMode enum)
 * @return 0 on success, -1 on error
 */
int BMP581_Driver_SetOutputDataRateRegister(BMP581_Driver *driver,
                                            BMP581_OutputDataRate odr,
                                            BMP581_PowerMode pm);

/**
 * @brief Get current BMP581 Output Data Rate
 * @param driver Pointer to BMP581_Driver structure
 * @return Current Output Data Rate (BMP581_OutputDataRate enum value)
 */
BMP581_OutputDataRate BMP581_Driver_GetOutputDataRate(BMP581_Driver *driver);

/**
 * @brief Get current BMP581 Power Mode
 * @param driver Pointer to BMP581_Driver structure
 * @return Current Power Mode (BMP581_PowerMode enum value)
 */
BMP581_PowerMode BMP581_Driver_GetPowerMode(BMP581_Driver *driver);