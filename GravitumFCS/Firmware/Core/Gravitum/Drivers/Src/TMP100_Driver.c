#include "TMP100_Driver.h"

int TMP100_Driver_Init(TMP100_Driver *driver, I2C_Controller *i2c_bus,
                       uint8_t i2c_address) {
  if (driver == NULL || i2c_bus == NULL) {
    return -1;
  }

  driver->i2c_address = i2c_address;
  driver->i2c_bus = i2c_bus;

  /* Set default resolution to 12-bit */
  TMP100_Driver_SetResolution(driver, TMP100_RES_12_BIT);

  return 0;
}

int TMP100_Driver_ReadTemp(TMP100_Driver *driver, float *temp) {
  if (driver == NULL || temp == NULL || driver->i2c_bus == NULL) {
    return -1;
  }

  uint8_t temp_data[2] = {0};

  /* Read 2 bytes from temperature register */
  int ret = I2C_Controller_Read(driver->i2c_bus, driver->i2c_address,
                                TMP100_REG_ADDR_TEMP, temp_data, 2);

  if (ret != 0) {
    return -1;
  }

  /* Convert raw data to temperature (TMP100 format: 12-bit, MSB first) */
  int16_t raw_temp = ((int16_t)temp_data[0] << 4) | (temp_data[1] >> 4);
  *temp =
      raw_temp *
      driver->resolution_factor; /* Apply resolution factor to get Celsius */

  return 0;
}

int TMP100_Driver_SetResolution(TMP100_Driver *driver, TMP100_Resolution bits) {
  if (driver == NULL || driver->i2c_bus == NULL) {
    return -1;
  }

  uint8_t config_data = 0;

  int ret = I2C_Controller_Read(driver->i2c_bus, driver->i2c_address,
                                TMP100_REG_ADDR_CONFIG, &config_data, 1);
  if (ret != 0) {
    return -1;
  }

  /* Clear resolution bits (bits 5-6) and set new resolution */
  config_data &= 0x9F; /* Clear bits 5-6 */
  config_data |= (((uint8_t)bits) << 5);

  /* Write updated config */
  ret = I2C_Controller_Write(driver->i2c_bus, driver->i2c_address,
                             TMP100_REG_ADDR_CONFIG, &config_data, 1);

  if (ret != 0) {
    return -1; /* I2C write failed */
  }

  driver->resolution = bits; /* Update driver state with new resolution */

  /** Update resolution factor based on new resolution */
  switch (bits) {
    case TMP100_RES_9_BIT:
      driver->resolution_factor = 0.5f;
      break;
    case TMP100_RES_10_BIT:
      driver->resolution_factor = 0.25f;
      break;
    case TMP100_RES_11_BIT:
      driver->resolution_factor = 0.125f;
      break;
    case TMP100_RES_12_BIT:
      driver->resolution_factor = 0.0625f;
      break;
    default:
      return -1; /* Invalid resolution */
  }

  return 0;
}

TMP100_Resolution TMP100_Driver_GetResolution(TMP100_Driver *driver) {
  if (driver == NULL || driver->i2c_bus == NULL) {
    return TMP100_RES_INVALID;
  }

  return driver->resolution;
}