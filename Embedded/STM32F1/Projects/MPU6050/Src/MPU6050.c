#include "MPU6050.h"
#include <string.h>

uint8_t mpu6050_init_gyro(I2C_HandleTypeDef *hi2c){
  uint8_t data[8] = {NULL};
  uint8_t address = DEFAULT_ADDRESS;
  uint8_t reg_address = NULL_VALUE;
  
  /* Write reset the whole module first */
  data[0] = 0x80;
  reg_address = PWR_MGMT_1;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  HAL_Delay(100); /* Wait for sensor's stablity */
  
  /* Write PLL with Z axis gyroscope reference */
  data[0] = CLOCK_PLL_ZGYRO;
  reg_address = PWR_MGMT_1;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting data rate 1kHz */
  data[0] = 0x01;
  reg_address = CONFIG;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting 500Hz sample rate ~ 2ms */
  data[0] = 0x01;
  reg_address = SMPLRT_DIV;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting Gyro full scale setting */
  data[0] = ACCEL_FS_16;
  reg_address = ACCEL_CONFIG;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write reset gyro and accel sensor  */
  data[0] = 0x07;
  reg_address = SIGNAL_PATH_RESET;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}
uint8_t mpu6050_init(I2C_HandleTypeDef *hi2c){
  uint8_t data[8] = {NULL};
  uint8_t address = NULL_VALUE;
  uint8_t reg_address = NULL_VALUE;
  
  /* Init variable */
  address = DEFAULT_ADDRESS;
  
  /* Read device if it is ready or not */
  if(HAL_I2C_IsDeviceReady(hi2c, address, 10, 0xFF) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Check device address */
  reg_address = WHO_AM_I;
  if(i2c_read(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  if(WHO_AM_I != data[0])
  {
    return HAL_ERROR;
  }

  /* Write reset bit to MPU6050 */
  data[0] = 0x80;
  reg_address = PWR_MGMT_1;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting data rate 1kHz */
  data[0] = RATE_1KHz;
  reg_address = SMPLRT_DIV;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting accelerometer */
  data[0] = 0xE0; /* Enable X, Y, Z self test, range +/- 2G */
  reg_address = ACCEL_CONFIG;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /* Write setting gyro */
  data[0] = 0xE0; /* Enable X, Y, Z self test, range +/- 250 degree */
  reg_address = GYRO_CONFIG;
  if(i2c_write(hi2c, address, reg_address, &data[0], 1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

uint8_t read_temperature(I2C_HandleTypeDef *hi2c, uint8_t *ptr)
{
  uint8_t data[14] = {NULL};
  uint8_t address = DEFAULT_ADDRESS;
  uint8_t reg_address = NULL_VALUE;
    
  /* Read temperature */
  reg_address = TEMP_OUT_H;
  if(i2c_read(hi2c, address, reg_address, &data[0], 14) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  memcpy(ptr, &data[0], 14);
  
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

uint8_t i2c_read_dma(I2C_HandleTypeDef *hi2c, uint8_t device_address, 
                  uint8_t memory_address, uint8_t *data, uint8_t number_of_bit)
{ 
  if(HAL_I2C_Mem_Read_DMA(hi2c, device_address, memory_address,
  I2C_MEMADD_SIZE_8BIT, &data[0], number_of_bit) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}