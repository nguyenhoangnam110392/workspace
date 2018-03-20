#include "delay.h"

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