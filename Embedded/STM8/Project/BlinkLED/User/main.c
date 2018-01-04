#include "stm8s.h"
#include "stm8s_conf.h"
#include "stm8s_tim4.h"

#define TIM4_PERIOD      124

void TIM4_Config(void);
void Delay(__IO uint32_t nTime);
static void CLK_Config(void);

__IO uint32_t TimingDelay = 0;

void main(void){
  CLK_Config();
  TIM4_Config();
  
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
  
  GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
  Delay(1000);
  GPIO_WriteLow(GPIOB, GPIO_PIN_5);
  while (1){
    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
    Delay(1000);
    
  }
}

void Delay(__IO uint32_t nTime){
  TimingDelay = nTime;
  while (TimingDelay != 0);
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

void TIM4_Config(void)
{
  /* TIM4 configuration:
  - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
  clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1  --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
  so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD); /* Time base configuration */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);                   /* Clear TIM4 update flag */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);              /* Enable update interrupt */
  enableInterrupts();                                 /* enable interrupts */
  TIM4_Cmd(ENABLE);                                   /* Enable TIM4 */
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line){ 
  while (1){}
}
#endif

