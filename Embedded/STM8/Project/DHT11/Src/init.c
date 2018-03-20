#include "init.h"

/** System Clock Configuration
*/
TIM_HandleTypeDef htim2;

void SystemClock_Config(void)
{
  CLK_DeInit();
  /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); 
  /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); 
  /* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void GPIO_Config(void){
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);
}
/***************************** END OF FILE ************************************/