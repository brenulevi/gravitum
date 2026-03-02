#include "BMP581_Driver.h"
#include <stdint.h>

int BMP581_Driver_Init(BMP581_Driver *driver, I2C_Controller *i2c_bus,
                       uint8_t i2c_address) {
  if (driver == NULL || i2c_bus == NULL) {
    return -1; // Invalid parameters
  }

  driver->i2c_address = i2c_address;
  driver->i2c_bus = i2c_bus;

  // Additional sensor initialization can be done here (e.g., reset, config)

  return 0; // Success
}

int BMP581_Driver_ReadTempAndPressure(BMP581_Driver *driver, float *temp,
                                      float *pressure) {
  if (driver == NULL || temp == NULL || pressure == NULL) {
    return -1; // Invalid parameters
  }

  uint8_t data[6]; // 3 bytes for temp, 3 bytes for pressure
  if (I2C_Controller_Read(driver->i2c_bus, driver->i2c_address,
                          BMP581_REG_ADDR_TEMP, data, sizeof(data)) != 0) {
    return -1; // Read error
  }

  int32_t temp_raw = (data[2] << 16) | (data[1] << 8) | data[0];
  int32_t press_raw = (data[5] << 16) | (data[4] << 8) | data[3];

  /* Manual Signal Extension */
  if (temp_raw & 0x800000) { // Check if negative
    temp_raw |= 0xFF000000; // Sign extend
  }

  *temp = (float) (temp_raw >> 16);
  *pressure = (float) (press_raw >> 6);

  return 0; // Success
}