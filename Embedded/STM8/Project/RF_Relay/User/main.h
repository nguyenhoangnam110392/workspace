#ifndef __MAIN_H
#define __MAIN_H

#include "stm8s.h" 
#include "stm8s_conf.h"
#include "stdbool.h"
#include "config.h"
#include "led.h"

void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void CLK_Config(void);
void GPIO_Config(void);
void TIM4_Config(void);
void TIM4_Callback(void);

#endif
