#include "nRF24L01.h"

u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  
u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  

u8 RX_BUF[TX_PLOAD_WIDTH];
u8 TX_BUF[TX_PLOAD_WIDTH];

u8 TxBuf[32]={
  0x01,0x02,0x03,0x4,0x05,0x06,0x07,0x08,
  0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
  0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,
  0x25,0x26,0x27,0x28,0x29,0x30,0x31,0x32
};

u8 sta;

void delay_us(u16 x){  // 16NOP = 1us
  u16 i;
  for(i=0;i < x;i++){
    asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
  }
}

void delay_ms(u16 x){ // not sure for the accurate time
  u16 i,j;
  for(i=0;i < 110;i++)
    for(j=0;j < x;j++);
}
void nRF_Init(void){
  delay_us(1000);
  CE=0;    // chip enable
  CSN=1;   // Spi disable 
  SCK=0;   // Spi clock line init high
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

u8 SPI_RW(u8 byte){       
  u8 i;
  for(i=0;i < 8;i++){
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
u8 SPI_RW_Reg(u8 reg, u8 value){
  u8 status;
  CSN = 0;                   
  status = SPI_RW(reg);      
  SPI_RW(value);             
  CSN = 1;                   
  return(status);            
}
/**************************************************/
u8 SPI_Read(u8 reg){
  u8 reg_val;
  CSN = 0;                    
  SPI_RW(reg);                
  reg_val = SPI_RW(0);        
  CSN = 1;                    
  return(reg_val);            
}

u8 SPI_Read_Buf(u8 reg, u8* pBuf, u8 bytes){
  u8 status, i;
  CSN = 0;                    
  status = SPI_RW(reg);      
  for(i=0; i<bytes; i++)
  pBuf[i] = SPI_RW(0);    
  CSN = 1;                    
  return(status);             
}
/**************************************************/
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 bytes)
{
  u8 status, i;
  CSN = 0;                    
  status = SPI_RW(reg);       
  delay_us(10);
  for(i=0; i<bytes; i++)
  SPI_RW(*pBuf++);        
  CSN = 1;                    
  return(status);             
}
/**************************************************/

void SetRX_Mode(void){
  CE = 1; 
  delay_us(1000); 
}
/**************************************************/

u8 RxPacket(u8* rx_buf){
  u8 revale=0;
  sta = SPI_Read(STATUS);	
  if(RX_DR)			{
    CE = 0; 			
    SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
    revale =1;			
  }
  SPI_RW_Reg(WRITE_REG+STATUS,sta);   
  return revale;
}
/**********************************************************************************************************/
void TxPacket(u8* tx_buf){
  CE=0;			                                         	
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 
  SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 		 
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);       
  CE = 1;		                            
  delay_us(1000);     
  CE = 0;                                     
}
