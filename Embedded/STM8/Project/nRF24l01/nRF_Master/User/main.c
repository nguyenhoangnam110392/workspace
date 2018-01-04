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
u8 data[32] = {0};

void main(void){     
  CLK_Init();     
  GPIO_Init();
  UART.Init();
  nRF_Init(); 
  
  while(1){
    RF2UART();          /* receive data from RF and send to UART*/
    UART2RF();          /* receive data from UART and send to RF*/
    sendDataFeedback();
    LED = 0;
    delay_ms(1000);
    LED = 1;
    delay_ms(1000);
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

void sendDataRF(u8 *array){
  TxPacket(array);                            // send data from UART to RF  
  u8 status = SPI_Read(STATUS);
  if(status & 0x20)
  {       LED = 0;        }
  else
  {       LED = 1;        }
  SPI_RW_Reg(WRITE_REG + STATUS, status);     // Clear the flags 
  delay_ms(1);
  nRF_Init();
  clearArray(array);
}

void clearArray(u8 *array){
  for (int i=0; i<sizeof(array); i++){
    array[i] = 0;
  }
}

void RF2UART(void){
  SetRX_Mode();        
  if(RxPacket(RxRF))  {	
    for(u8 i=0;i<32;i++){
      UART.sendData(RxRF[i]);
    }	
  }
}

void UART2RF(void){
  if(UART1_SR_RXNE){
    RxUART[rxIndex++] = UART1_DR;
    
    if(rxIndex > 31) {
      sendDataRF(RxUART);    
      rxIndex = 0;      // reset counter variable  
    }
  }
}

void sendDataFeedback(void){
  data_typedef data_frame;
  Sensor_TypeDef sensor;
  
  sensor.temperature_data = 0x12;   /* 0~255 */
  sensor.humid_data   = 0x34;       /* 0~255 */    
  sensor.light_data   = 0x56;       /* 0~255 */
  sensor.motion_data  = 0x78;       /* 0~255 */
  sensor.current_data = 0x99;       /* 0~255 */
  
  UART.Create_sensorFeedback(&data_frame, &sensor);
  
  for(int i=0; i<sizeof(data_frame.payLoad); i++){
    data[i] = data_frame.payLoad[i];
  }
                 
  sendDataRF(data);
}