/* Includes ------------------------------------------------------------------*/
#include "stm8s.h" 
#include "stm8s_conf.h"
#include "stdbool.h"
#include "PID.h"
#include "PID_Current.h"

#define TIM4_PERIOD       24

#define Current_set       3000
#define Voltage_set       29600
#define delta             5
#define dutyMax           355        /* 25kHz = 640
                                       30kHz = 533
                                       35kHz = 457
                                       40kHz = 400
                                       45kHz = 355
                                       50kHz = 320  */
bool startPID = false;
float k_vi;
float k_duty;
int duty = 0;

__IO uint32_t TimingDelay = 0;

float ADC_Current=0;
float ADC_Current_Temp;
float ADC_Voltage=0;
bool priority = true;
bool init_run = true;
int flag = 0;
uint16_t loop_Counter;

int timeTick;

float in;
float out;
double setpoint;
float pre;

static void TIM1_Config(void);
static void TIM4_Config(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void ADC_Config(void);
void ADC_Config2(void);
uint16_t ADC_read(void);
static void CLK_Config(void);
void read_voltage(void);
void read_current(void);
void control(void);
void set_duty(uint16_t duty);
void protect(void);
void First_Time(void);
     
void main(void){
  CLK_Config();
  TIM1_Config(); 
  TIM4_Config();
  
  PID_Init(&in, &out, &setpoint, &timeTick, &startPID);
  
  k_vi = (float)Voltage_set/Current_set;
  k_duty = (float)1000/dutyMax;
  
  First_Time();
  
  set_duty(0);
  
  while (1){
    
    loop_Counter++;
    
    //if (loop_Counter % 5 == 0){
      read_voltage();
      read_current();
      
    
    control();
    protect();
    Delay(1);
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

static void TIM1_Config(void){
  TIM1_DeInit();
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, dutyMax, 0);
  
  /*TIM1_Pulse = CCR3_Val*/
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,\
               duty, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,\
               TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR4_Val*/
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, duty, TIM1_OCPOLARITY_LOW,
               TIM1_OCIDLESTATE_SET);
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
}

static void TIM4_Config(void){
  /* TIM4 configuration:
  - TIM4CLK is set to 2 MHz, the TIM4 Prescaler is equal to 4 so the TIM1 counter
  clock used is 16 MHz / 64 = 250 000 Hz
  - We need to generate a time base equal to 0.1 ms
  so TIM4_PERIOD = (0.0001 * 250000 - 1) = 24 */

  TIM4_TimeBaseInit(TIM4_PRESCALER_64, TIM4_PERIOD); /* Time base configuration */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);                   /* Clear TIM4 update flag */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);              /* Enable update interrupt */
  enableInterrupts();                                 /* enable interrupts */
  TIM4_Cmd(ENABLE);                                   /* Enable TIM4 */
}

void ADC_Config(void){
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D2, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3, DISABLE);
  enableInterrupts();
}

void ADC_Config2(void){
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_4, ADC1_PRESSEL_FCPU_D2, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL4, DISABLE);
  enableInterrupts();
}

uint16_t ADC_read(void){
  ADC1_StartConversion();
  uint16_t adcValue = ADC1_GetConversionValue();
  return adcValue;
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
void read_voltage(void){
  ADC_Config();
  ADC_Voltage = (float)((delta * ADC_read() * 54.2) + ((1000 - delta) * ADC_Voltage)) / 1000;
}

void read_current(void){
  ADC_Config2();
  ADC_Current_Temp = ADC_read();
  ADC_Current_Temp = ADC_Current_Temp - 509;
  if(ADC_Current_Temp < 0)  ADC_Current_Temp = 0;
  ADC_Current_Temp = ADC_Current_Temp * 49.27;
  ADC_Current = (float)((delta * ADC_Current_Temp) + ((1000 - delta) * ADC_Current)) / 1000;
}

void control(void){
  if(ADC_Voltage > k_vi * ADC_Current){
    setpoint = Voltage_set;
    in = ADC_Voltage;
    PID_Update(setpoint);
    flag = 1;
  }
  else{
    setpoint = k_vi * Current_set;
    in = ADC_Current * k_vi;
    PID_Update(setpoint);
    flag = 0;
  }
  
  PID_Run();
}

void protect(void){
  if((ADC_Current > (float)Current_set * 1.2) || (ADC_Voltage > (float)Voltage_set * 1.1)){
    if(out > 1)    out = out - 1;
  }
  
  duty = (int)(out/k_duty);
  set_duty(duty);
}

void set_duty(uint16_t duty){
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,\
               duty, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,\
               TIM1_OCNIDLESTATE_RESET);

  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, duty, TIM1_OCPOLARITY_LOW,\
               TIM1_OCIDLESTATE_SET);
}

void First_Time(void){
  Delay(100);
  ADC_Config();
  ADC_Voltage = ADC_read() * 54.2;
  
  ADC_Config2();
  ADC_Current_Temp = ADC_read();
  ADC_Current_Temp = ADC_Current_Temp - 509;
  if(ADC_Current_Temp < 0)  ADC_Current_Temp = 0;
  ADC_Current_Temp = ADC_Current_Temp * 49.27;
  ADC_Current = ADC_Current_Temp;
  
  Delay(1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){ 
  while (1)
  {}
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
