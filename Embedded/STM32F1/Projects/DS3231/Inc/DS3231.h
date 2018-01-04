#ifndef DS3231_H
#define DS3231_H

#include "stm32f1xx_hal.h"

/* API */
uint8_t MPU6050_Init();
void read_time_dma(uint8_t *ptrData);

/* Specific define value */
#define DS3231_ADDRESS		       0x68 /* DS3231 address */
#define DS3231_WRITE_BIT               0x00
#define DS3231_READ_BIT                0x01

#define DS3231_WRITE_ADDRESS           (DS3231_ADDRESS << 1) | DS3231_WRITE_BIT
#define DS3231_READ_ADDRESS            (DS3231_ADDRESS << 1) | DS3231_READ_BIT

#define DS3231_SECOND_ADDRESS  	       0x00 
#define DS3231_MINUTE_ADDRESS          0x01
#define DS3231_HOUR_ADDRESS            0x02
#define DS3231_DAY_OF_WEEK_ADDRESS     0x03
#define DS3231_DAY_OF_MONTH_ADDRESS    0x04
#define DS3231_MONTH_ADDRESS           0x05
#define DS3231_YEAR_ADDRESS            0x06

#define DS3231_CONTROL  	0x0E 
#define DS3231_MSB  		0x11 

/* Declare function */
uint8_t set_time(uint8_t year, uint8_t month, uint8_t date, uint8_t day_of_week,
                 					uint8_t hour, uint8_t minute, uint8_t second);
#endif

