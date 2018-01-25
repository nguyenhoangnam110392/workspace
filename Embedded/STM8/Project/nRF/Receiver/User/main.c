#include "main.h"

static void CLK_Config(void);
static void Port_Config(void);

static uint8_t data[7] = {0x01, 0x02, 0x00, 0x04, 0x05, 0x06, 0x07};

void main(void){
  /* Initialize configuration */
  CLK_Config();
  Port_Config();
  nRF24L01_Pin_Config(); 
  
  //EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);
  //enableInterrupts();
  //nRF24L01_Set_RxMode();
  uint8_t *ptr = &data[0];
  EEPROM_Write_Value(ptr);
  while (1){
    //nRF24L01_RevData(data);
    //halt();
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
  GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);
}

void delay_us(uint16_t x)
{
  uint16_t i;
  for(i=0;i < x;i++){
    asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
  }
}

void delay_ms(uint16_t x)
{
  for(int i=0; i < x; i++)
  {
    delay_us(1000);
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line){ 
  while (1){}
}
#endif

