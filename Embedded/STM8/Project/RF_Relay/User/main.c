/* Includes ------------------------------------------------------------------*/

#include "main.h"

uint16_t hour = 0;
uint32_t tick = 0;
__IO uint32_t TimingDelay = 0;

void main(void){
  CLK_Config();
  GPIO_Config();
  TIM4_Config();

  Start_up();
  
  Relay(ON);
  
  while(1){
    
    if(GPIO_ReadInputPin(CMD_A_PORT, CMD_A_PIN)){
      Relay(ON);
    }
    else if(GPIO_ReadInputPin(CMD_B_PORT, CMD_B_PIN)){
      Relay(OFF);
      hour = 0;
      tick = 0;
      LED_0();
    }
    else if(GPIO_ReadInputPin(CMD_C_PORT, CMD_C_PIN)){
      if(hour < 5){hour++;  tick = hour * MULTI;  Relay(ON);  Delay(280);}
    }
    else if(GPIO_ReadInputPin(CMD_D_PORT, CMD_D_PIN)){
      if(hour > 0){hour--;  tick = hour * MULTI;  Relay(ON);  Delay(280);}
    }
    
    switch (hour){
      case 0: LED_0();   break;
      case 1: LED_1();   break;
      case 2: LED_2();   break;
      case 3: LED_3();   break;
      case 4: LED_4();   break;
      case 5: LED_5();   break;
    }
    
  }
}

void CLK_Config(void){
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); /* Configure the HSI prescaler to the optimal value */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);/* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
}

void GPIO_Config(void){
  GPIO_Init(RELAY_1_PORT, RELAY_1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(RELAY_2_PORT, RELAY_2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  
  GPIO_Init(LED_1_PORT, LED_1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED_2_PORT, LED_2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED_3_PORT, LED_3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED_4_PORT, LED_4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED_5_PORT, LED_5_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  
  GPIO_Init(CMD_A_PORT, CMD_A_PIN, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CMD_B_PORT, CMD_B_PIN, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CMD_C_PORT, CMD_C_PIN, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CMD_D_PORT, CMD_D_PIN, GPIO_MODE_IN_FL_NO_IT);
}  

void TIM4_Config(void){
  /*TIM4CLK  16 MHz, Prescaler 128 -> 16 MHz / 128 = 125 000 Hz
  - In this example we need to generate a time base equal to 1 ms
  so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD); /* Time base configuration */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);                   /* Clear TIM4 update flag */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);              /* Enable update interrupt */
  enableInterrupts();                                 /* enable interrupts */
  TIM4_Cmd(ENABLE);                                   /* Enable TIM4 */
}

void Delay(__IO uint32_t nTime){
  TimingDelay = nTime;
  while (TimingDelay != 0);
}

void TimingDelay_Decrement(void){
  if (TimingDelay != 0x00){
    TimingDelay--;
  }
}

void TIM4_Callback(void){
  if(tick > 0){        
    tick--;
    hour = tick / MULTI + 1;
    if(tick == 0){ hour = 0;  Relay(OFF);}
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  while (1)
  {}
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
