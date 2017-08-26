#ifndef __INIT_
#define __INIT_

#include "main.h"

#define PORTA   0x01
#define PORTB   0x02
#define PORTC   0x03
#define PORTD   0x04
#define PORTE   0x05

void SystemClock_Config(void);
void GPIO_Config(void);
void GPIO_Init(uint8_t PORTx, uint16_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed);

#endif