#ifndef __MAIN_H
#define __MAIN_H

#include "stm8s.h" 
#include "stm8s_conf.h"
#include "stdbool.h"
#include "config.h"
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void CLK_Config(void);
void ADC_Config(void);
void GPIO_Config(void);
void TIM1_Config(void);
void TIM4_Config(void);

uint16_t ADC_read(void);

#define dutyMax       500
#define TIM4_PERIOD   124

uint16_t duty = 100;

int timeTick;
__IO uint32_t TimingDelay = 0;
#endif
