#include "nRF24L01.h"

uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  
uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};

uint8_t sta;

void delay_us(uint16_t x){
  uint16_t i;
  for(i=0;i < x;i++){
    asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
  }
}

void delay_ms(uint16_t x){ 
  uint16_t i,j;
  for(i=0;i < 110;i++)
    for(j=0;j < x;j++);
}

void nRF_Init(void){
  delay_us(1000);
  CE = 0;    /* chip enable */
  CSN = 1;   /* Spi disable */
  SCK = 0;   /* Spi clock line init high */
  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); 
  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      
  SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   
  SPI_RW_Reg(WRITE_REG + RF_CH, 0);         	
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); 
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);  
  SPI_RW_Reg(WRITE_REG + CONFIG, 0X0F);
  delay_ms(2);
}

void SetRX_Mode(void){
  CE = 1; 
  delay_ms(1); 
}
/**************************************************/

uint8_t nrf_read(uint8_t* rx_buf){
  uint8_t revale=0;
  sta = SPI_Read(STATUS);	
  if(RX_DR){
    CE = 0; 			
    SPI_Read_Buf(RD_RX_PLOAD, rx_buf,TX_PLOAD_WIDTH);/* read receive payload from RX_FIFO buffer */
    revale =1;			
  }
  SPI_RW_Reg(WRITE_REG+STATUS,sta);   
  return revale;
}
/**********************************************************************************************************/
void nrf_send(uint8_t* tx_buf){
  CE=0;			                                         	
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 
  SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 		 
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);       
  CE = 1;		                            
  delay_us(1000);     
  CE = 0;                                     
}

/**********************************************************************************************************/
uint8_t SPI_RW(uint8_t byte){       
  uint8_t i;
  for(i = 0;i < 8;i++){
    if((byte & 0x80) == 0){       
      MOSI = 0;       
    }
    else{       
      MOSI = 1;       
    }
    
    byte = (byte << 1);                
    SCK = 1;
    
    if(MISO == 1){       
      byte |= 1;      
    }
    else{       
      byte |= 0;      
    }
    SCK = 0;
  }
  return (byte);    
}
/***************************************************/
uint8_t SPI_RW_Reg(uint8_t reg, uint8_t value){
  uint8_t status;
  CSN = 0;                   
  status = SPI_RW(reg);      
  SPI_RW(value);             
  CSN = 1;                   
  return(status);            
}
/**************************************************/
uint8_t SPI_Read(uint8_t reg){
  uint8_t reg_val;
  CSN = 0;                    
  SPI_RW(reg);                
  reg_val = SPI_RW(0);        
  CSN = 1;                    
  return(reg_val);            
}

uint8_t SPI_Read_Buf(uint8_t reg, uint8_t* pBuf, uint8_t bytes){
  uint8_t status, i;
  CSN = 0;                    
  status = SPI_RW(reg);      
  for(i=0; i<bytes; i++)
  pBuf[i] = SPI_RW(0);    
  CSN = 1;                    
  return(status);             
}
/**************************************************/
uint8_t SPI_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes)
{
  uint8_t status, i;
  CSN = 0;                    
  status = SPI_RW(reg);       
  for(i=0; i<bytes; i++)
  SPI_RW(*pBuf++);        
  CSN = 1;                    
  return(status);             
}
/**************************************************/