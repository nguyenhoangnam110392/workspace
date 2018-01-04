/* Includes ------------------------------------------------------------------*/

#include "main.h"

void main(void){
  CLK_Config();
  ADC_Config();
  GPIO_Config();
  TIM1_Config();
  TIM4_Config();

  while(1){
    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
    Delay(1000);
  }
}

void CLK_Config(void){
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); /* Configure the HSI prescaler to the optimal value */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);/* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
}

void ADC_Config(void){
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_4, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL4, DISABLE);
  enableInterrupts();
}

void GPIO_Config(void){
  GPIO_Init(STANDBY_PORT, STANDBY_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(MUTE_PORT, MUTE_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(STATUS_PORT, STATUS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(ONOFF_PORT, ONOFF_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(ENABLE_POWER_PORT, ENABLE_POWER_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}  
  
void TIM1_Config(void){
  TIM1_DeInit();
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, dutyMax, 0);  /*Prescale = 1, 16Mhz*/
  
  /*TIM1_Pulse = CCR3_Val*/
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, duty, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR4_Val*/
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, duty, TIM1_OCPOLARITY_LOW,TIM1_OCIDLESTATE_SET);
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
}

void TIM4_Config(void)
{
  /*TIM4CLK  16 MHz, Prescaler 128 -> 16 MHz / 128 = 125 000 Hz
  - In this example we need to generate a time base equal to 1 ms
  so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD); /* Time base configuration */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);                   /* Clear TIM4 update flag */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);              /* Enable update interrupt */
  enableInterrupts();                                 /* enable interrupts */
  TIM4_Cmd(ENABLE);                                   /* Enable TIM4 */
}

uint16_t ADC_read(void){
  ADC1_StartConversion();
  uint16_t adcValue = ADC1_GetConversionValue();
  return adcValue;
}

void temperature_control(){
  uint16_t temperature = ADC_read();
  if(temperature > 35){
  }
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

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  while (1)
  {}
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
