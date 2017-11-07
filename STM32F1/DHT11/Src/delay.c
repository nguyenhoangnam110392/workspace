#include "delay.h"

void delay_us(uint32_t nus){     
  uint32_t temp;         
  uint8_t fac_us=9; 
  
  SysTick->LOAD=nus*fac_us;         
  SysTick->VAL=0x00;     
  SysTick->CTRL=0x01 ;       
  do
  {
    temp=SysTick->CTRL;
  }
  while(temp&0x01&&!(temp&(1<<16)));
  SysTick->CTRL=0x00;   
  SysTick->VAL =0X00; 
}

void delay_ms(uint16_t ms){
  while( ms-- ){
    delay_us(999);
  }
}   