#include "nRF24L01.h"


static u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  
static u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  

u8 RX_BUF[TX_PLOAD_WIDTH];
u8 TX_BUF[TX_PLOAD_WIDTH];

u8 sta;
u8 gtemp[5];

u8 SE8R01_DR_2M = 0;  //choose 1 of these to set the speed
u8 SE8R01_DR_1M = 0;
u8 SE8R01_DR_500K = 1;

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
  while(x){
    x--;
    delay_us(600);
  }
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
    
    SCK = 1;
    byte = (byte << 1);                 
    
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
/**************************************************/
u8 SPI_Read_Buf(u8 reg, u8* pBuf, u8 bytes){
  u8 status, i;
  CSN = 0;                    
  status = SPI_RW(reg);      
  for(i=0; i<bytes; i++){
    pBuf[i] = SPI_RW(0);   
  }
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
  for(i=0; i<bytes; i++){
    SPI_RW(*pBuf++);
  }
  CSN = 1;                    
  return(status);             
}

void rf_switch_bank(unsigned char bankindex)
{
  unsigned char temp0,temp1;
  temp1 = bankindex;
  
  temp0 = SPI_RW(iRF_BANK0_STATUS);
  
  if((temp0&0x80)!=temp1)
  {
    SPI_RW_Reg(iRF_CMD_ACTIVATE,0x53);
  }
}

void se8r01_powerup()
{
  rf_switch_bank(iBANK0);
  SPI_RW_Reg(iRF_CMD_WRITE_REG|iRF_BANK0_CONFIG,0x03);
  SPI_RW_Reg(iRF_CMD_WRITE_REG|iRF_BANK0_RF_CH,0x32);
  SPI_RW_Reg(iRF_CMD_WRITE_REG|iRF_BANK0_RF_SETUP,0x48);
  SPI_RW_Reg(iRF_CMD_WRITE_REG|iRF_BANK0_PRE_GURD,0x77); //2450 calibration
}

void se8r01_calibration()
{
  rf_switch_bank(iBANK1);
  
  gtemp[0]=0x40;
  gtemp[1]=0x00;
  gtemp[2]=0x10;
  gtemp[3]=0xE6;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_PLL_CTL0, gtemp, 4);
  
  gtemp[0]=0x20;
  gtemp[1]=0x08;
  gtemp[2]=0x50;
  gtemp[3]=0x40;
  gtemp[4]=0x50;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_CAL_CTL, gtemp, 5);
  
  gtemp[0]=0x00;
  gtemp[1]=0x00;
  gtemp[2]=0x1E;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_IF_FREQ, gtemp, 3);
  
  gtemp[0]=0x29;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_FDEV, gtemp, 1);
  
  gtemp[0]=0x00;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_DAC_CAL_LOW, gtemp, 1);
  
  gtemp[0]=0x7F;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_DAC_CAL_HI, gtemp, 1);
  
  gtemp[0]=0x02;
  gtemp[1]=0xC1;
  gtemp[2]=0xEB;
  gtemp[3]=0x1C;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_AGC_GAIN, gtemp, 4);
  
  gtemp[0]=0x97;
  gtemp[1]=0x64;
  gtemp[2]=0x00;
  gtemp[3]=0x81;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_RF_IVGEN, gtemp, 4);
  
  rf_switch_bank(iBANK0);
  
  CE = 1;
  delay_us(30);
  CE = 0;
  
  delay_us(50);                            // delay 50ms waitting for calibaration.
  
  CE = 1;
  delay_us(30);
  CE = 0;
  
  delay_us(50);                            // delay 50ms waitting for calibaration.
}

void se8r01_setup()
{
  gtemp[0]=0x28;
  gtemp[1]=0x32;
  gtemp[2]=0x80;
  gtemp[3]=0x90;
  gtemp[4]=0x00;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK0_SETUP_VALUE, gtemp, 5);
  
  delay_ms(2);
  
  rf_switch_bank(iBANK1);
  
  gtemp[0]=0x40;
  gtemp[1]=0x01;
  gtemp[2]=0x30;
  gtemp[3]=0xE2;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_PLL_CTL0, gtemp, 4);
  
  gtemp[0]=0x29;
  gtemp[1]=0x89;
  gtemp[2]=0x55;
  gtemp[3]=0x40;
  gtemp[4]=0x50;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_CAL_CTL, gtemp, 5);
  
  gtemp[0]=0x29;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_FDEV, gtemp, 1);
  
  gtemp[0]=0x55;
  gtemp[1]=0xC2;
  gtemp[2]=0x09;
  gtemp[3]=0xAC;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_RX_CTRL, gtemp, 4);
  
  gtemp[0]=0x00;
  gtemp[1]=0x14;
  gtemp[2]=0x08;
  gtemp[3]=0x29;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_FAGC_CTRL_1, gtemp, 4);
  
  gtemp[0]=0x02;
  gtemp[1]=0xC1;
  gtemp[2]=0xCB;
  gtemp[3]=0x1C;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_AGC_GAIN, gtemp, 4);
  
  gtemp[0]=0x97;
  gtemp[1]=0x64;
  gtemp[2]=0x00;
  gtemp[3]=0x01;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_RF_IVGEN, gtemp, 4);
  
  gtemp[0]=0x2A;
  gtemp[1]=0x04;
  gtemp[2]=0x00;
  gtemp[3]=0x7D;
  SPI_Write_Buf(iRF_CMD_WRITE_REG|iRF_BANK1_TEST_PKDET, gtemp, 4);
  
  rf_switch_bank(iBANK0);
}

void radio_settings()
{
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_EN_AA, 0x01);       //enable auto acc on pip 1
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_EN_RXADDR, 0x01);   //enable pip 1
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_SETUP_AW, 0x02);    //4 byte adress
  
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_SETUP_RETR, 0x7A);  //lowest 4 bits 0-15 rt transmisston higest 4 bits 256-4096us Auto Retransmit Delay
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_RF_CH, 40);
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_RF_SETUP, 0x4f);    //2mps 0x4f
  //SPI_RW_Reg(WRITE_REG|iRF_BANK0_DYNPD, 0x01);     //pipe0 pipe1 enable dynamic payload length data
  //SPI_RW_Reg(WRITE_REG|iRF_BANK0_FEATURE, 0x07);   // enable dynamic paload lenght; enbale payload with ack enable w_tx_payload_noack
  
  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    //from tx
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);                // Select same RX payload width as TX Payload width
}

void power_off(void)
{
  CE = 0;
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0D); 
  CE = 1;
  delay_us(20);
}

void SE8R01_Calibration(void)
{
  unsigned char temp[5];
  rf_switch_bank(iBANK0);
  temp[0] = 0x03;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_CONFIG, temp, 1);

  temp[0] = 0x32;

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_RF_CH, temp, 1);



  if (SE8R01_DR_2M == 1)
  {
    temp[0] = 0x48;
  }
  else if (SE8R01_DR_1M == 1)
  {
    temp[0] = 0x40;
  }
  else
  {
    temp[0] = 0x68;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_RF_SETUP, temp, 1);
  temp[0] = 0x77;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_PRE_GURD, temp, 1);

  rf_switch_bank(iBANK1);
  temp[0] = 0x40;
  temp[1] = 0x00;
  temp[2] = 0x10;
  if (SE8R01_DR_2M == 1)
  {
    temp[3] = 0xE6;
  }
  else
  {
    temp[3] = 0xE4;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_PLL_CTL0, temp, 4);

  temp[0] = 0x20;
  temp[1] = 0x08;
  temp[2] = 0x50;
  temp[3] = 0x40;
  temp[4] = 0x50;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_CAL_CTL, temp, 5);

  temp[0] = 0x00;
  temp[1] = 0x00;
  if (SE8R01_DR_2M == 1)
  {
    temp[2] = 0x1E;
  }
  else
  {
    temp[2] = 0x1F;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_IF_FREQ, temp, 3);

  if (SE8R01_DR_2M == 1)
  {
    temp[0] = 0x29;
  }
  else
  {
    temp[0] = 0x14;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_FDEV, temp, 1);

  temp[0] = 0x00;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_DAC_CAL_LOW, temp, 1);

  temp[0] = 0x7F;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_DAC_CAL_HI, temp, 1);

  temp[0] = 0x02;
  temp[1] = 0xC1;
  temp[2] = 0xEB;
  temp[3] = 0x1C;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_AGC_GAIN, temp, 4);
  //--
  temp[0] = 0x97;
  temp[1] = 0x64;
  temp[2] = 0x00;
  temp[3] = 0x81;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_RF_IVGEN, temp, 4);
  rf_switch_bank(iBANK0);

  CE = 1;
  delay_us(30);
  CE = 0;

  delay_ms(50);                            // delay 50ms waitting for calibaration.

  CE = 1;
  delay_us(30);
  CE = 0;

  delay_ms(50);                            // delay 50ms waitting for calibaration.
}


void SE8R01_Analog_Init(void)           //SE8R01 ???
{
  gtemp[0] = 0x28;
  gtemp[1] = 0x32;
  gtemp[2] = 0x80;
  gtemp[3] = 0x90;
  gtemp[4] = 0x00;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_SETUP_VALUE, gtemp, 5);
  delay_ms(2);

  unsigned char temp[5];

  rf_switch_bank(iBANK1);

  temp[0] = 0x40;
  temp[1] = 0x01;
  temp[2] = 0x30;
  if (SE8R01_DR_2M == 1)
  {
    temp[3] = 0xE2;
  }
  else
  {
    temp[3] = 0xE0;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_PLL_CTL0, temp, 4);

  temp[0] = 0x29;
  temp[1] = 0x89;
  temp[2] = 0x55;
  temp[3] = 0x40;
  temp[4] = 0x50;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_CAL_CTL, temp, 5);

  if (SE8R01_DR_2M == 1)
  {
    temp[0] = 0x29;
  }
  else
  {
    temp[0] = 0x14;
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_FDEV, temp, 1);

  temp[0] = 0x55;
  temp[1] = 0xC2;
  temp[2] = 0x09;
  temp[3] = 0xAC;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_RX_CTRL, temp, 4);

  temp[0] = 0x00;
  temp[1] = 0x14;
  temp[2] = 0x08;
  temp[3] = 0x29;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_FAGC_CTRL_1, temp, 4);

  temp[0] = 0x02;
  temp[1] = 0xC1;
  temp[2] = 0xCB;
  temp[3] = 0x1C;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_AGC_GAIN, temp, 4);

  temp[0] = 0x97;
  temp[1] = 0x64;
  temp[2] = 0x00;
  temp[3] = 0x01;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_RF_IVGEN, temp, 4);

  gtemp[0] = 0x2A;
  gtemp[1] = 0x04;
  gtemp[2] = 0x00;
  gtemp[3] = 0x7D;
  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK1_TEST_PKDET, gtemp, 4);

  rf_switch_bank(iBANK0);
}

void SE8R01_Init(void)
{
  unsigned char temp[5];
  SE8R01_Calibration();
  SE8R01_Analog_Init();

  if (SE8R01_DR_2M == 1)
  {
    temp[0] = 0x4f;  //2MHz,+5dbm
  }
  else if  (SE8R01_DR_1M == 1)
  {
    temp[0] = 0x47;   //1MHz,+5dbm
  }
  else
  {
    temp[0] = 0x6f;   //500K,+5dbm
  }

  SPI_Write_Buf(iRF_CMD_WRITE_REG | iRF_BANK0_RF_SETUP, temp, 1);

  SPI_RW_Reg(WRITE_REG|iRF_BANK0_EN_AA, 0x01);       //enable auto acc on pip 1
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_EN_RXADDR, 0x01);   //enable pip 1
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_SETUP_AW, 0x02);    //4 byte adress
  SPI_RW_Reg(WRITE_REG | iRF_BANK0_RF_CH, 40);

  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    //from tx
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);                // Select same RX payload width as TX Payload width
  SPI_RW_Reg(WRITE_REG | iRF_BANK0_CONFIG, 0x3f);
  SPI_RW_Reg(WRITE_REG | iRF_BANK0_DYNPD, 0x3f);        // enable dynamic payload length data
  SPI_RW_Reg(WRITE_REG | iRF_BANK0_FEATURE, 0x07);      // enable dynamic paload lenght; enbale payload with ack enable w_tx_payload_noack
}

void RF_send(u8 *array)
{
  u8 tmp_status = SPI_Read(STATUS);	
  CE=0;			                                         	
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 
  SPI_Write_Buf(WR_TX_PLOAD, array, TX_PLOAD_WIDTH); 		 
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   
  CE = 1;		                            
  delay_ms(1);     
  CE = 0;  
  
  
  delay_ms(10);
  SPI_RW(FLUSH_TX);      
  SPI_RW_Reg(WRITE_REG + STATUS, 0xff);
  nRF_fake_init_tx();
}

u8 RF_receive(u8* array)
{
  u8 success = 0;
  delay_ms(1);
  status = SPI_Read(STATUS);	
  if(RX_DR){
    CE = 0; 			
    SPI_Read_Buf(RD_RX_PLOAD, array, TX_PLOAD_WIDTH);  //read receive payload from RX_FIFO buffer 		
    success = 1;
  }
  SPI_RW_Reg(WRITE_REG+STATUS, status); 
  
  delay_ms(10);
  SPI_RW(FLUSH_RX);   
  SPI_RW_Reg(WRITE_REG + STATUS, 0xff);
 
  nRF_fake_init_rx();
  
  return success;
}

void nRF_fake_init_tx(void){
  status = SPI_Read(STATUS);
  CE = 0;
  delay_ms(1);
  SE8R01_Init();
  
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_CONFIG, 0x3E);
  CE = 1;
}

void nRF_fake_init_rx(void){
  power_off();
  delay_us(1);
  se8r01_powerup();
  delay_us(1);
  
  status = SPI_Read(STATUS);
  CE = 0;
  delay_ms(1);
  SE8R01_Init();
  
  SPI_RW_Reg(WRITE_REG|iRF_BANK0_CONFIG, 0x3F); 
  CE = 1;
}