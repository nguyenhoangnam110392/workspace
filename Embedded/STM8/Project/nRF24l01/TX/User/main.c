/*********************************************************************
Fun   :    STM8S103F3P6 SPI nRF24L01
Author:    LTREE
Date  :    2014.08.20
Descr :    
Detail:    Transmission 
*********************************************************************/
#include "main.h"

u8 tx_buffer[32]={0};
u8 value = 0;

void main(void){       
  CLK_Init();    /* HSI fCPU = fMaster = 16MHz */
  GPIO_Init();  
  nRF_Init();  
  
  while(1){
    /* Generate value for array */
    if(value++ >= 0xFA)
    {
      value = 0;
    }
    for(u8 i=0; i<32; i++)
    {
      tx_buffer[i] = value + i;
    }
    nrf_send(tx_buffer);                
    u8 status = SPI_Read(STATUS);
    if(status & 0x20)
    {       LED = 0;        }
    else
    {       LED = 1;        }
    SPI_RW_Reg(WRITE_REG + STATUS, status);     /* Clear the flags */
    delay_ms(1000);
  }
}

void CLK_Init(void){ 
  //Automatic Mode
  CLK_ICKR |= 0X01;          // HSIEN = 1
  while(!(CLK_ICKR & 0X02)); // HSIRDY = 1
  CLK_CKDIVR = 0X00;         // factor 1 1 -> fMaster = fCPU = 16MHz
  CLK_SWCR |= 0X02;          // SWEN = 1
  CLK_SWR = 0XE1;            // HSI selected       
  while(CLK_SWCR & 0x01);    // SWBSY = 0          
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
