/*********************************************************************
Fun   :    SPI nRF24L01
Author:    LTREE
Date  :    2014.08.20
Descr :    
Detail:    Receiver
*********************************************************************/
#include "main.h"

u8 RxRF[32] = {0}; 
u8 RxUART[32] = {0};
u8 rxIndex = 0;

void main(void){     
  CLK_Init();     
  GPIO_Init();
  UART.Init();
  nRF_Init(); 
  while(1){
    SetRX_Mode();        
    if(nrf_read(RxRF))  {	
       for(u8 i=0;i<32;i++){
          UART.sendData(RxRF[i]);
       }	
    }
    u8 tmp_data = UART.getData();
    if(tmp_data)  {RxUART[rxIndex++] = tmp_data;}
    if(rxIndex > 32)    {rxIndex = 0;}
  }
}

void CLK_Init(void){ 
  //Automatic Mode - HSI fCPU = fMaster = 16MHz 
  CLK_ICKR |= 0X01;          // HSIEN = 1
  while(!(CLK_ICKR & 0X02)); // HSIRDY = 1
  CLK_CKDIVR = 0X00;         // factor 1 1 -> fMaster = fCPU = 16MHz
  CLK_SWCR |= 0X02;          // SWEN = 1
  CLK_SWR = 0XE1;            // HSI selected       
  while(CLK_SWCR & 0x01);    // SWBSY = 0          
  CLK_PCKENR1 |= 0X08;       // UART1 Enable the clock
}

void GPIO_Init(void){
  PC_DDR = 0XDF; //PC5 Input -- MISO
  PA_DDR = 0X00; //PA3 Input -- IRQ
  PC_CR1 = 0XFF; //Push-up & Pull-up
  PA_CR1 = 0X08; //PA3 Pull-up
  PC_CR2 = 0XDF; //Fast Mode
  PA_CR2 = 0X08; //PA3 Without interrupt
  //LED PB5
  PB_DDR_bit.DDR5 = 1; 
  PB_CR1_bit.C15 = 1;
  PB_CR2_bit.C25 = 1;
  LED = 1;
}
