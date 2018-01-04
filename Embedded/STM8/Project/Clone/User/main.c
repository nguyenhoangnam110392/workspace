/* Includes ------------------------------------------------------------------*/

#include "main.h"

__IO uint32_t TimingDelay = 0;
float temperature = 0;

void main(void){  
  CLK_Config();
  GPIO_Config();
  TIM4_Config();
  ADC_Config();
  
  while(1){
    temperature = (ADC_read()*100.0*5.0)/1024.0;
    temperature_control(temperature);
    
    if(GPIO_ReadInputPin(RPI_SIGNAL_PORT, RPI_SIGNAL_PIN)){  /*Logic high*/
      GPIO_WriteHigh(CHARGER_PORT, CHARGER_PIN);        /* Turn on charger */
    }
    else{
      GPIO_WriteLow(CHARGER_PORT, CHARGER_PIN);         /* Turn off charger */
    }
    
    Delay(1);
  }
}

void CLK_Config(void){
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); /* Configure the HSI prescaler to the optimal value */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);/* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
}

void GPIO_Config(void){
  GPIO_Init(LM35_PORT, LM35_PIN, GPIO_MODE_IN_FL_NO_IT);           /* Input floating */
  
  GPIO_Init(CHARGER_PORT, CHARGER_PIN, GPIO_MODE_OUT_PP_LOW_FAST); /* Output push-pull */
  GPIO_Init(RPI_PORT, RPI_PIN, GPIO_MODE_OUT_PP_LOW_FAST);         /* Output push-pull */
  
  GPIO_Init(RPI_SIGNAL_PORT, RPI_SIGNAL_PIN, GPIO_MODE_IN_FL_NO_IT);/* Input floating */
  GPIO_Init(TOUCH_PORT, TOUCH_PIN, GPIO_MODE_IN_FL_NO_IT);          /* Input floating */
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

void ADC_Config(void){
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL4, DISABLE);
  enableInterrupts();             /* set ADC channel here */
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

}

uint16_t ADC_read(void){
  ADC1_StartConversion();
  uint16_t adcValue = ADC1_GetConversionValue();
  return adcValue;
}

void temperature_control(float temp){
  if(temp > TEMP_HIGH){
    GPIO_WriteLow(RPI_PORT, RPI_PIN);    /* Turn off Raspberry power */
  }
  else if(temp < TEMP_LOW){
    GPIO_WriteHigh(RPI_PORT, RPI_PIN);   /* Turn on Raspberry power */
  }
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  while (1)
  {}
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
