#include "MPU6050.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t MPU6050_Init(){
  uint8_t retVal = MPU_NOT_OK;
  uint8_t address = 0;
  uint8_t data;
  uint32_t lastevent = 0;
    
  address = 0xD0;
  I2C1->CR1 |= 0x0100;
  
  while(!retVal){
    uint32_t flag1 = 0, flag2 = 0;
    flag1 = I2C1->SR1;
    flag2 = I2C1->SR2;
    flag2 = flag2 << 16;
    
    lastevent = (flag1 | flag2) & 0x00FFFFFF;
    if ((lastevent & 0x00030001) == 0x00030001){
      retVal = MPU_OK;
    }
  }
  /*
  if(HAL_I2C_IsDeviceReady(&hi2c1, address, 10, 0xFF) != HAL_OK){
    retVal = MPU_NOT_OK;
  }
  
  data = MPU6050_RA_WHO_AM_I;
  retVal = MPU_OK;
  if(HAL_I2C_Master_Transmit(&hi2c1, address, &data, 1, 0xFF) != HAL_OK)
  {
     retVal = MPU_NOT_OK;
  }
  
  uint8_t d[2];
  d[0] = 0x6B;
  d[1] = 0x00;

  if(HAL_I2C_Master_Transmit(&hi2c1, address , d, 2, 0xFF) != HAL_OK)
  {
     retVal = MPU_NOT_OK;
  }*/
  return retVal;
}