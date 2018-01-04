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
bool start_ok = false;
u8 tmp;
u16 tick;

void main(void){     
  CLK_Init();     
  GPIO_Init();
  UART.Init();
  nRF_Init(); 
  
  while(1){
    RF2UART();          /* receive data from RF and send to UART*/
    UART2RF();          /* receive data from UART and send to RF*/
    //sendDataFeedback();
    delay_ms(1);
    tick++;
    if(tick%200==0){    LED = !LED;     }
  }
}

void CLK_Init(void){ 
  /*Automatic Mode - HSI fCPU = fMaster = 16MHz */
  CLK_ICKR |= 0X01;          /* HSIEN = 1 */
  while(!(CLK_ICKR & 0X02)); /* HSIRDY = 1 */
  CLK_CKDIVR = 0X00;         /* factor 1 1 -> fMaster = fCPU = 16MHz */
  CLK_SWCR |= 0X02;          /* SWEN = 1 */
  CLK_SWR = 0XE1;            /* HSI selected  */     
  while(CLK_SWCR & 0x01);    /* SWBSY = 0  */        
  CLK_PCKENR1 |= 0X08;       /* UART1 Enable the clock */
}

void GPIO_Init(void){
  PC_DDR = 0XDF; /*PC5 Input -- MISO*/
  PA_DDR = 0X00; /*PA3 Input -- IRQ*/
  PC_CR1 = 0XFF; /*Push-up & Pull-up*/
  PA_CR1 = 0X08; /*PA3 Pull-up*/
  PC_CR2 = 0XDF; /*Fast Mode*/
  PA_CR2 = 0X08; /*PA3 Without interrupt*/
  
  PB_DDR_bit.DDR5 = 1; /* PB5 output */
  PB_CR1_bit.C15 = 1;
  PB_CR2_bit.C25 = 1;
  
  PB_DDR_bit.DDR4 = 1; /* PB4 output */
  PB_CR1_bit.C14 = 1;
  PB_CR2_bit.C24 = 1;
  
  PD_DDR_bit.DDR3 = 1; /* PD3 output */
  PD_CR1_bit.C13 = 1;
  PD_CR2_bit.C23 = 1;
}

void RF2UART(void){     /* receive data from RF and send to UART*/
  SetRX_Mode();        
  if(RxPacket(RxRF)){
    if(UART.isPacketValid(&RxRF[0])){
      tmp = RxRF[DataArray.command_1];
      
      RELAY_1 = RxRF[DataArray.command_1];
      RELAY_2 = RxRF[DataArray.command_1];
      /*
      for(u8 i=0;i<32;i++){
        UART.sendData(RxRF[i]);
      }	*/
    }
  }
}

void UART2RF(void){ 
  /* while (!(UART1_SR_RXNE));      wait until uart is not empty */
  if(UART1_SR_RXNE){
    PD_ODR |= (1<<2);
    
    if(UART1_DR==0xAA){    start_ok = true;           } /* start receive data if start bit matched */
    if(start_ok)      { RxUART[rxIndex++] = UART1_DR; }
      
    if(rxIndex > 31) {
      sendDataRF(RxUART);    
      rxIndex = 0;      /* reset counter variable  */
      start_ok = false; /* reset flag start bit */
    }
  }
}

void sendDataFeedback(void){
  data_typedef data_frame;
  Sensor_TypeDef sensor;
  
  sensor.data_relay_1 = RxRF[DataArray.command_1];   /* 0~255 */
  sensor.data_relay_2 = 0;   /* 0~255 */    
  sensor.data_relay_3 = 0;   /* 0~255 */
  sensor.data_relay_4 = 0;   /* 0~255 */
  sensor.data_relay_5 = 0;   /* 0~1   */
  
  UART.Create_sensorFeedback(&data_frame, &sensor);
  
  for(int i=0; i<sizeof(data_frame.payLoad); i++){
    data[i] = data_frame.payLoad[i];
  }
                 
  sendDataRF(data);
}

void sendDataRF(u8 *array){
  TxPacket(array);                            /* send data from UART to RF */ 
  u8 status = SPI_Read(STATUS);
  if(status & 0x20)
  {               }
  else
  {               }
  SPI_RW_Reg(WRITE_REG + STATUS, status);     /* Clear the flags */
  delay_ms(1);
  nRF_Init();
  clearArray(array);
}

void clearArray(u8 *array){
  for (int i=0; i<sizeof(array); i++){
    array[i] = 0;
  }
}