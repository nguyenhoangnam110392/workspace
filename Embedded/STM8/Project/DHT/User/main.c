#include "main.h"
#include <string.h>
#include <stdbool.h>
#include "DHT11.h"
#include <stdio.h>
#include <stdlib.h>

static void CLK_Config(void);
static void Port_Config(void);
static void TIM2_Config(void);

/* Variables */
uint8_t data[5];
uint16_t temp = 0;
uint16_t humid = 0;
uint16_t sum = 0;

void main(void){
  /* Initialize configuration */
  CLK_Config();
  Port_Config();
  TIM2_Config();
  OneWire_Init(GPIOA, GPIO_PIN_2);
  
  uint8_t *ptr = calloc(5, sizeof(uint8_t));
  while (1){    
    DHT_ReadAll(ptr);
    
    memcpy(data, &ptr[0], 5); 
    humid = (data[1] << 7) | data[0];
    temp = (data[3] << 7) | data[2];
    sum = data[0] + data[1] + data[2] + data[3];
  }
}

static void CLK_Config(void){
  CLK_DeInit();
  /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  /* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

static void Port_Config(void){
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
}

static void TIM2_Config(void)
{
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_16, 0xFFFF);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line){ 
  while (1){}
}
#endif

