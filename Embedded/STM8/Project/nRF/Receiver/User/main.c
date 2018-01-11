#include "main.h"

static void CLK_Config(void);
uint8_t data[32] = {0};

void main(void){
  /* Initialize configuration */
  CLK_Config();

  nRF24L01_Pin_Config(); 

  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1){
    nRF24L01_Set_RxMode();

    nRF24L01_RevData(data);
    
    /* Led blinking */
    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
    delay_ms(500);
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

