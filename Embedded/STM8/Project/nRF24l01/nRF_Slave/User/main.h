#ifndef __MAIN_H_
#define __MAIN_H_

#include <iostm8.h>
#include "lt_stm8s_macro.h"
#include "LT_STM8_Vectors.h"
#include "nRF24L01.h"
#include "UART.h"

void CLK_Init(void);
void GPIO_Init(void);
void sendDataRF(void);
void clearArray(u8 array);

#endif
