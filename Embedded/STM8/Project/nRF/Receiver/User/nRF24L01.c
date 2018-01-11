/*       Pin configuration map
 *------------------------------------*
 *             IRQ : MISO -- C7       *
 *      C6 -- MOSI : SCK  -- C5       *
 *      C4 --  CSN : CE   -- C3       *
 *      VCC -- VCC : GND  -- GND      *
 *------------------------------------*/

#include "nRF24L01.h"
#include <string.h>

#define SPI_FAILED     0
#define SPI_OK         1

uint8_t TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};  
uint8_t RX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};

static uint8_t nRF24L01_Read_RxData(uint8_t RegAddr, uint8_t *RxData, uint8_t DataLen);
static uint8_t nRF24L01_Write_TxData(uint8_t RegAddr,uint8_t *TxData, uint8_t DataLen);
static uint8_t nRF24L01_Read_Reg(uint8_t RegAddr);
static uint8_t nRF24L01_Write_Reg(uint8_t RegAddr, uint8_t data);
static uint8_t nRF24L01_SPI_RW(uint8_t data);
static void nRF24L01_SPI_WAIT(void);
static void CE(uint8_t state);
static void CSN(uint8_t state);

/*******************************************************************************
 * Name: NRF24L01_Pin_Config
 * Function: nRF24L01 control pin initialization and SPI module initialization
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
void nRF24L01_Pin_Config(void)
{
  SPI_DeInit();
  /* Initialize SPI - high first, 6M, main mode, SCK idle low, the first edge 
   * of the data acquisition */
  SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
                                 SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, \
                       SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
  
  SPI_Cmd(ENABLE);  /* Enable SPI */
  
  /* CSN pin is initialized to output*/
  GPIO_Init(CE_PORT, CE_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  /* CE pin is initialized to output */
  GPIO_Init(CSN_PORT, CSN_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

/*******************************************************************************
 * Name: nRF24L01_Set_TxMode
 * Function: Set nRF24L01 to send mode
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
void nRF24L01_Set_TxMode(void)
{
  CE(0); 
  
  /* Set the sending address and address length */
  nRF24L01_Write_TxData(W_REGISTER+TX_ADDR, TX_ADDRESS, TX_ADDR_WITDH); 
  /* In order to answer the receiving device, the receive channel 0 address 
   * is the same as the send address */
  nRF24L01_Write_TxData(W_REGISTER+RX_ADDR_P0, TX_ADDRESS, TX_ADDR_WITDH);  

  /******The following register configuration**************/
  /* Enable Receive Channel 0 Auto Answer */
  nRF24L01_Write_Reg(W_REGISTER+EN_AA, 0x01);
  /* Enable receive channel 0 */
  nRF24L01_Write_Reg(W_REGISTER+EN_RXADDR, 0x01);
  /* Automatic re-transmission delay waiting 250us+86us, 10 times */
  nRF24L01_Write_Reg(W_REGISTER+SETUP_RETR, 0x0a);
  /* Select RF channel 0x40 */
  nRF24L01_Write_Reg(W_REGISTER+RF_CH, 0x40);
  /* Data transfer rate 1Mbps, transmit power 0dBm, low noise amplifier gain */
  nRF24L01_Write_Reg(W_REGISTER+RF_SETUP, 0x07);
  /* CRC enable, 16-bit CRC check, power-on */ 
  nRF24L01_Write_Reg(W_REGISTER+CONFIG, 0x0e);
  
  CE(1);

  delay_us(20); /* Follow the chip manual for more than 10us seconds */
}

/*******************************************************************************
 * Name: nRF24L01_SendData
 * Function: send data function
 * Parameter: data -> point to send data pointer
 * Returns: None
 * Description:
 ******************************************************************************/
void nRF24L01_SendData(uint8_t *data)
{
  /* Chip Enable Off */
  CE(0);
  /* Write to send the data */
  nRF24L01_Write_TxData(W_TX_PAYLOAD, data, TX_DATA_WITDH);
  /* Chip Enable On */
  CE(1);
  
  delay_ms(5);
}

/*******************************************************************************
 * Name: nRF24L01_Read_RxData
 * Function: Read the data function of nRF24L01RX FIFO
 * Parameter: RegAddr -> nRF24L01 register address
 * Rxdata -> Pointer to the data area
 * DataLen -> data length
 * Returns: The data returned by nRF24L01
 * Description: Used in receive mode
 ******************************************************************************/
static uint8_t nRF24L01_Read_RxData(uint8_t RegAddr, uint8_t *RxData, uint8_t DataLen)
{ 
  uint8_t retVal, i;
  
  CSN(0);                 /* 启动时序 */
  retVal = nRF24L01_SPI_RW(RegAddr);  /* 写入要读取的寄存器地址 */
  for(i = 0; i < DataLen; i++)      /* 读取数据 */
  {
    RxData[i] = nRF24L01_SPI_RW(0);
  } 
  
  CSN(1);
  
  return retVal; 
}

/*******************************************************************************
 * Name: nRF24L01_Write_TxData
 * Function: Data function written to nRF24L01TX FIFO
 * Parameter: RegAddr -> nRF24L01 register address
 * Rxdata -> Pointer to the data to be written
 * DataLen -> data length
 * Returns: The data returned by nRF24L01
 * Description: Used in send mode
 ******************************************************************************/
static uint8_t nRF24L01_Write_TxData(uint8_t RegAddr,uint8_t *TxData,uint8_t DataLen)
{ 
  uint8_t retVal, i;
  
  CSN(0);
  retVal = nRF24L01_SPI_RW(RegAddr);  /* 写入要写入寄存器的地址 */
  for(i = 0; i < DataLen; i++)      /* 写入数据 */
  {
    nRF24L01_SPI_RW(*TxData++);
  }   
  
  CSN(1);
  return retVal ;
}

/*******************************************************************************
 * Name: nRRF24L01_CheckACK
 * Function: Detect sending success and clear flag function
 * Parameter: 0 - sent successfully, 1- - failed to send
 * Returns: None
 * Description:
 ******************************************************************************/
uint8_t nRRF24L01_CheckACK(void)
{  
  uint8_t retVal;
  
  /* Read status register value after sending */
  retVal = nRF24L01_Read_Reg(R_REGISTER + STATUS);   
  /* Whether there is a send complete interrupt and repeat send interrupt */
  if((retVal & 0x20) || (retVal & 0x10))
  {
     /* Clear TX_DS or MAX_RT interrupt flag */
     nRF24L01_Write_Reg(W_REGISTER + STATUS, 0xff); 
     CSN(0);
     nRF24L01_SPI_RW(FLUSH_TX); /* Used to clear the FIFO */
     CSN(1); 
     return SPI_OK;
  }
  else
  {
     return SPI_FAILED;
  }
}

/*******************************************************************************
 * Name: nRF24L01_Read_Reg
 * Function: Read nRF24L01 register function
 * Parameter: RegAddr -> nRF24L01 register address
 * Returns: The data returned by nRF24L01
 * Description: None 
 ******************************************************************************/
static uint8_t nRF24L01_Read_Reg(uint8_t RegAddr)
{
   uint8_t retVal;
   
   CSN(0);                          /* Start timing */
   nRF24L01_SPI_RW(RegAddr);        /* Write register address */
   retVal = nRF24L01_SPI_RW(0x00);  /* Write register read instruction */ 
   CSN(1);
   
   return retVal;                   /* Return status value */
}

/*******************************************************************************
 * Name: nRF24L01_Write_Reg
 * Function: Write data function to nRF24L01 register
 * Parameter: RegAddr -> nRF24L01 register address
 * data -> Data written to the register
 * Returns: The data returned by nRF24L01
 * Description: None
 ******************************************************************************/
static uint8_t nRF24L01_Write_Reg(uint8_t RegAddr,uint8_t data)
{
   uint8_t retVal;
   
   CSN(0);                              /* Start timing */
   retVal = nRF24L01_SPI_RW(RegAddr);   /* Write address */
   nRF24L01_SPI_RW(data);               /* Write value */
   CSN(1);
   
   return retVal;
}

/*******************************************************************************
 * Name: nRF24L01_SPI_RW
 * Function: Read/Write data using SPI
 * Parameter: data -> SPI->DR
 * Return: SPI->DR
 * Description: Write data and read value from SPI register
 ******************************************************************************/
uint8_t nRF24L01_SPI_RW(uint8_t data)
{
  /* Wait for previous transmissions to complete if DMA TX enabled for SPI */
  nRF24L01_SPI_WAIT();
  /* Fill output buffer with data */
  SPI_SendData(data);
  /* Wait for transmissions to complete */
  nRF24L01_SPI_WAIT();

  return SPI_ReceiveData();
}

/*******************************************************************************
 * Name: nRF24L01_SPI_WAIT
 * Function: Wait for transmissions to complete
 * Parameter: None
 * Return: None
 * Description: None 
 ******************************************************************************/
void nRF24L01_SPI_WAIT(void)
{
  while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
}

/*******************************************************************************
 * Name: CE
 * Function: Switch pin value of Chip Enable pin
 * Parameter: CE to HIGH or LOW
 * Return: None
 * Description: Reduce the command length
 ******************************************************************************/
void CE(uint8_t state)
{
  if(state){
    GPIO_WriteHigh(CE_PORT, CE_PIN);
  }
  else{
    GPIO_WriteLow(CE_PORT, CE_PIN);
  }
}

/*******************************************************************************
 * Name: CSN
 * Function: Switch pin value of Chip Selection pin
 * Parameter: CSN to HIGH or LOW
 * Return: None
 * Description: Reduce the command length
 ******************************************************************************/
void CSN(uint8_t state){
  if(state){
    GPIO_WriteHigh(CSN_PORT, CSN_PIN);
  }
  else{
    GPIO_WriteLow(CSN_PORT, CSN_PIN);
  }
}
 /***************************** END OF FILE ***********************************/

/*******************************************************************************
 * 名称: nRF24L01_Set_RxMode
 * 功能: 将nRF24L01TX FIFO设置为接收模式
 * 形参: 无
 * 返回: 无
 * 说明: 
 ******************************************************************************/
void nRF24L01_Set_RxMode(void)
{
  CE(0); 
  /* 接收设备接收通道0使用和发送设备相同的发送地址 */
  nRF24L01_Write_TxData(W_REGISTER+RX_ADDR_P0, TX_ADDRESS, TX_ADDR_WITDH);  
  
  /******下面有关寄存器配置**************/
  nRF24L01_Write_Reg(W_REGISTER+EN_AA,0x01);       /* 使能接收通道0自动应答 */
  nRF24L01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);   /* 使能接收通道0 */
  nRF24L01_Write_Reg(W_REGISTER+RF_CH,0x40);       /* 选择射频通道0x40 */
  nRF24L01_Write_Reg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  /* 接收通道0选择和发送通道相同有效数据宽度 */
  nRF24L01_Write_Reg(W_REGISTER+RF_SETUP,0x07);    /* 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益 */
  nRF24L01_Write_Reg(W_REGISTER+CONFIG,0x0f);      /* CRC使能，16位CRC校验，上电 */ 

  CE(1);

  delay_us(20); /* 按照芯片手册要求 保持10us秒以上 */
  
}

/*******************************************************************************
 * 名称: nRF24L01_RevData
 * 功能: 接收数据函数
 * 形参: RevData -> 指向存放数据缓冲区
 * 返回: 1--接收数据失败，0--接收数据成功
 * 说明: 
 ******************************************************************************/
uint8_t nRF24L01_RevData(uint8_t *RevData)
{
  uint8_t RevFlags = 1;
  uint8_t sta;
  
  sta = nRF24L01_Read_Reg(R_REGISTER+STATUS); /* 读取状态寄存器的值 */
  if(sta & 0x40)        /* 判断是否接收到数据 */
  {
    CE(0);      
    nRF24L01_Read_RxData(R_RX_PAYLOAD,RevData,RX_DATA_WITDH); /* 从RXFIFO读取4位数据 */
    
    /* 接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志 */
    nRF24L01_Write_Reg(W_REGISTER+STATUS,0xff); 
    
    CSN(0);
      nRF24L01_SPI_RW(FLUSH_RX);  /* 用于清空FIFO */
      CSN(1); 
    
    RevFlags = 0;    
  }
  
  return(RevFlags);
}

/*************************接收数据*********************************************/
void GetDate(uint8_t *data)
{
  uint8_t sta;
    sta=nRF24L01_Read_Reg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
    if(sta&0x40)        // 判断是否接收到数据
     {
     CE(0);//CE=0;//待机
     nRF24L01_Read_RxData(R_RX_PAYLOAD,data,RX_DATA_WITDH);// 从RXFIFO读取数据 接收4位即可，后一位位结束位
     
    
     nRF24L01_Write_Reg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
     CSN(0);//CSN=0;
     nRF24L01_SPI_RW(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
     CSN(1);//CSN=1;    
     
     }
    //NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标   
}