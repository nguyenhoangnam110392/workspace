/*********************************************************************
Fun   :    SPI nRF24L01
Author:    LTREE
Date  :    2014.08.20
Descr :    
Detail:    Receiver
*********************************************************************/
#include "main.h"

u8 RxBuf[11]; 
u8 RxUART[11] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
u8 rxIndex = 0;
u8 data[32] = {0};
bool start_ok = false;
u8 tmp;
u16 tick;
u8 status;

u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  
u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01}; 

u8 TxBuf[32];

void main(void){ 
  CLK_Init();     
  GPIO_Init();
  UART.Init();	
  
  //nRF_fake_init_tx();  delay_ms(1); nRF_fake_init_tx();  sendDataRF(RxUART);
  nRF_fake_init_rx();nRF_fake_init_rx();

  while(1){
  /*
    UART2RF();
 
    tick++;
    if(tick >= 100){RxUART[0] = tmp++;  sendDataRF(RxUART); tick = 0;}
   */
    
    if(RF_receive(RxBuf)){
      LED = !LED;
    }
    delay_ms(100);
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
  PC_DDR = 0XDF;        /*PC5 Input -- MISO*/
  PA_DDR = 0X00;        /*PA3 Input -- IRQ*/
  PC_CR1 = 0XFF;        /*Push-up & Pull-up*/
  PA_CR1 = 0X08;        /*PA3 Pull-up*/
  PC_CR2 = 0XDF;        /*Fast Mode*/
  PA_CR2 = 0X08;        /*PA3 Without interrupt*/
  
  PB_DDR_bit.DDR5 = 1;  /* PB5 output */
  PB_CR1_bit.C15 = 1;
  PB_CR2_bit.C25 = 1;
  
  PB_DDR_bit.DDR4 = 1;  /* PB4 output */
  PB_CR1_bit.C14 = 1;
  PB_CR2_bit.C24 = 1;
  
  PD_DDR_bit.DDR3 = 1;  /* PD3 output */
  PD_CR1_bit.C13 = 1;
  PD_CR2_bit.C23 = 1;
  
  CE = 0;	        // chip enable
  CSN = 1;              // Spi disable	
}

void UART2RF(void){ 
  /* while (!(UART1_SR_RXNE));      wait until uart is not empty */
 
  
  if(UART1_SR_RXNE){
    PD_ODR |= (1<<2);
    
    if(UART1_DR==0xAA){    start_ok = true;           } /* start receive data if start bit matched */
    if(start_ok)      { RxUART[rxIndex++] = UART1_DR; }
      
    if(rxIndex > 11) {    
      rxIndex = 0;      /* reset counter variable  */
      start_ok = false; /* reset flag start bit */
      sendDataRF(RxUART);
    }
  }
}

void sendDataRF(u8 *array){     /* send data from UART to RF */ 
  RF_send(array);                           
  //clearArray(array);
}

void clearArray(u8 *array){
  for (int i=0; i<sizeof(array); i++){
    array[i] = 0;
  }
}

void sendDataFeedback(void){
  data_typedef data_frame;
  Sensor_TypeDef sensor;
  
  sensor.data_relay_1 = RxBuf[DataArray.command_1];   /* 0~255 */
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

void IWDGInit(void) 
{  
  IWDG_KR = 0x55;      //Disable Watchdog
  IWDG_PR = 0x05;       //f/128 *255=510ms
  IWDG_RLR = 0xFF;      //count =255 
  IWDG_KR = 0xAA;       //refresh count 
  IWDG_KR = 0xCC;       //enable wdg 
}  