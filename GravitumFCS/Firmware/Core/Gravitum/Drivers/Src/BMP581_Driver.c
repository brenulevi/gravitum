#include "BMP581_Driver.h"
#include <stdint.h>

int BMP581_Driver_Init(BMP581_Driver *driver, I2C_Controller *i2c_bus,
                       uint8_t i2c_address) {
  if (driver == NULL || i2c_bus == NULL) {
    return -1;
  }

  driver->i2c_address = i2c_address;
  driver->i2c_bus = i2c_bus;

  if (BMP581_Driver_SetOutputDataRateRegister(driver, BMP581_ODR_120_HZ, BMP581_PM_NORMAL) != 0) {
    driver->odr = BMP581_ODR_INVALID;
    driver->power_mode = BMP581_PM_INVALID;
    return -1;
  }

  return 0;
}

int BMP581_Driver_ReadTempAndPressure(BMP581_Driver *driver, float *temp,
                                      float *pressure) {
  if (driver == NULL || temp == NULL || pressure == NULL) {
    return -1;
  }

  uint8_t data[6]; // 3 bytes for temp, 3 bytes for pressure
  if (I2C_Controller_Read(driver->i2c_bus, driver->i2c_address,
                          BMP581_REG_ADDR_TEMP, data, sizeof(data)) != 0) {
    return -1;
  }

  int32_t temp_raw = (data[2] << 16) | (data[1] << 8) | data[0];
  int32_t press_raw = (data[5] << 16) | (data[4] << 8) | data[3];

  /* Manual Signal Extension */
  if (temp_raw & 0x800000) {
    temp_raw |= 0xFF000000;
  }

  *temp = (float) (temp_raw >> 16);
  *pressure = (float) (press_raw >> 6);

  return 0;
}

int BMP581_Driver_SetOutputDataRateRegister(BMP581_Driver *driver, BMP581_OutputDataRate odr, BMP581_PowerMode pwr_mode) {
  if (driver == NULL || driver->i2c_bus == NULL) {
    return -1;
  }

  /* ODR is in bits 2:6 of the register */
  /* Power Mode is in bits 0:1 of the register */
  uint8_t odr_value = (((uint8_t)odr << 2) & 0x7C) | ((uint8_t)pwr_mode & 0x03);

  if (I2C_Controller_Write(driver->i2c_bus, driver->i2c_address,
                           BMP581_REG_ADDR_ODR, &odr_value, 1) != 0) {
    return -1;
  }

  driver->odr = odr;
  driver->power_mode = pwr_mode;
  return 0; 
}

BMP581_OutputDataRate BMP581_Driver_GetOutputDataRate(BMP581_Driver *driver) {
  if (driver == NULL || driver->i2c_bus == NULL) {
    return BMP581_ODR_INVALID;
  }

  return driver->odr;
}

BMP581_PowerMode BMP581_Driver_GetPowerMode(BMP581_Driver *driver) {
  if (driver == NULL || driver->i2c_bus == NULL) {
    return BMP581_PM_INVALID;
  }

  return driver->power_mode;
}