#ifndef __INIT_
#define __INIT_

#include "main.h"

void SystemClock_Config(void);
void GPIO_Config(void);
void GPIO_Init(GPIO_TypeDef *GPIOx, uint16_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed);
void Timer2_Config(void);
void I2C1_Config(void);

#define PORTA 0x01
#define PORTB 0x02
#define PORTC 0x03
#define PORTD 0x04

#endif