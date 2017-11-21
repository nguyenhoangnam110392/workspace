#include "MPU6050.h"

uint8_t mpu6050_init(I2C_HandleTypeDef *hi2c, uint8_t *ptr){
  uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  /* Read device if it is ready or not */
  if(HAL_I2C_IsDeviceReady(hi2c, DEFAULT_ADDRESS, 10, 0xFF) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Read device address */
  if(i2c_read(hi2c, DEFAULT_ADDRESS, WHO_AM_I, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Write reset bit to MPU6050 */
  data[0] = 0x80;
  if(i2c_write(hi2c, DEFAULT_ADDRESS, PWR_MGMT_1, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting data rate 1kHz */
  data[0] = RATE_1KHz;
  if(i2c_write(hi2c, DEFAULT_ADDRESS, SMPLRT_DIV, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting accelerometer */
  data[0] = 0xE0; /* Enable X, Y, Z self test, range +/- 2G */
  if(i2c_write(hi2c, DEFAULT_ADDRESS, ACCEL_CONFIG, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting gyro */
  data[0] = 0xE0; /* Enable X, Y, Z self test, range +/- 250 degree */
  if(i2c_write(hi2c, DEFAULT_ADDRESS, GYRO_CONFIG, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

uint8_t read_temperature()
{
  return HAL_OK;
}

uint8_t i2c_read(I2C_HandleTypeDef *hi2c, uint8_t device_address, 
                  uint8_t memory_address, uint8_t *data, uint8_t number_of_bit)
{

  if(HAL_I2C_Mem_Read(hi2c, device_address, memory_address,
  I2C_MEMADD_SIZE_8BIT, &data[0], number_of_bit, 0xFF) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

uint8_t i2c_write(I2C_HandleTypeDef *hi2c, uint8_t device_address, 
                  uint8_t memory_address, uint8_t *data, uint8_t number_of_bit)
{
  if(HAL_I2C_Mem_Write(hi2c, device_address, memory_address,
  I2C_MEMADD_SIZE_8BIT, &data[0], number_of_bit, 0xFF) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}