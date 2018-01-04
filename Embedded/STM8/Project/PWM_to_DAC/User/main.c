/* Includes ------------------------------------------------------------------*/
#include "stm8s.h" 
#include "stm8s_conf.h"
#include "stdbool.h"
#include "PID.h"
#include "PID_Current.h"

#define dutyMax   16000             /* 1khz  = 16000
                                       25kHz = 640
                                       30kHz = 533
                                       35kHz = 457
                                       40kHz = 400
                                       45kHz = 355
                                       50kHz = 320  */
uint16_t duty = 0;

void TIM1_Config(void);
void CLK_Config(void);
void set_duty(uint16_t duty);
void Delay (uint16_t nCount);

     
void main(void){
  CLK_Config();
  TIM1_Config(); 
  
  set_duty(0);
  while (1){
    duty = duty + 70;
    set_duty(duty);
    if(duty >= dutyMax){    duty = 0;       }
    Delay(0xFFFF);
  }
}

void CLK_Config(void){
    CLK_DeInit();                               /* Configure the Fcpu to DIV1*/  
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);    /* Configure the HSI prescaler to the optimal value */ 
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);   
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);/* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
}

void TIM1_Config(void){
  TIM1_DeInit();
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, dutyMax, 0);
  
  /*TIM1_Pulse = CCR3_Val*/
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 0, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR4_Val*/
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, 0, TIM1_OCPOLARITY_LOW,TIM1_OCIDLESTATE_SET);
  
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
}

void set_duty(uint16_t duty){
  /*TIM1_Pulse = CCR4_Val*/
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, duty, TIM1_OCPOLARITY_LOW,TIM1_OCIDLESTATE_SET);
}

void Delay(uint16_t nCount){
  while (nCount > 0){
    nCount--;
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  while (1)
  {}
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
