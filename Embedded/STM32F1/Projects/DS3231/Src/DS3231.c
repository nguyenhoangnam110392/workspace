#include "DS3231.h"
#include <string.h>

extern I2C_HandleTypeDef hi2c1;

uint8_t set_time(uint8_t year, uint8_t month, uint8_t date, uint8_t day_of_week,
                 uint8_t hour, uint8_t minute, uint8_t second)
{
  uint8_t data[7];
  uint8_t retVal = HAL_OK;
  
  /* Set date time in to array */
  data[0] = second;
  data[1] = minute;
  data[2] = hour;
  data[3] = day_of_week;
  data[4] = date;
  data[5] = month;
  data[6] = year;

  /* Write data to register */
  HAL_I2C_Mem_Write(&hi2c1, DS3231_WRITE_ADDRESS, 0, I2C_MEMADD_SIZE_8BIT, \
                                                             &data[0], 7, 0xFF); 
  
  /* Verify that data was written ok */
  HAL_I2C_Mem_Read(&hi2c1, DS3231_READ_ADDRESS, 0, I2C_MEMADD_SIZE_8BIT, \
                                                             &data[0], 7, 0xFF);
  
  /* Compare written data with input data */
  if(data[0]==second && data[1]==minute && data[2]==hour && data[3]==day_of_week \
     && data[4]==date && data[5]==month && data[6]==year)
  {
    retVal = HAL_OK;
  }
  else
  {
    retVal = HAL_ERROR;
  }
  
  return retVal;
}

void read_time_dma(uint8_t *ptrData)
{
  uint8_t data[7];
  HAL_I2C_Mem_Read_IT(&hi2c1, DS3231_READ_ADDRESS, DS3231_SECOND_ADDRESS,\
                                       I2C_MEMADD_SIZE_8BIT, &data[0], 7); 
  memcpy(&ptrData[0], &data[0], 7);
}