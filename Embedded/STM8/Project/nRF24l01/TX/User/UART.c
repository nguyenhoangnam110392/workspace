#include "UART.h"

void sendData(u8 data){
  while(!(UART1_SR & 0X80));
  UART1_DR = data;
  while(!(UART1_SR & 0X40));
}
 
u8 getData(void){
  u8 tmp_data = 0;
  if(UART1_SR_RXNE){
    tmp_data = UART1_DR;
  }
  return tmp_data;
}

void Init(void){
  UART1_CR1 = 0X00;
  UART1_CR2 = 0X00;
  UART1_CR3 = 0X00;
  UART1_BRR2 = 0X0b; //Baud Rate 115200
  UART1_BRR1 = 0X08;       
  UART1_CR2 = 0X2c; 
}
