#include "main.h"

static void CLK_Config(void);
static void TIM2_Config(void);
static void TM1650_Set(uint8_t address, uint8_t data);

/* Variables */
uint8_t data[5] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF};
uint16_t temp = 0;
uint16_t humid = 0;
uint16_t sum = 0;
uint8_t NUMBER[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void main(void){
  /* Initialize configuration */
  CLK_Config();
  //TIM2_Config();
  
  //uint8_t *ptr = calloc(5, sizeof(uint8_t));
  
  I2C_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,ENABLE);
  I2C_Cmd(ENABLE);
  I2C_Init(40000, 0x00, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);

  while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY));

  I2C_GenerateSTART(ENABLE);
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(0x48, I2C_DIRECTION_TX);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(0x11);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING))
  
  //
  I2C_SendData(0x68);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_SendData(0x3f);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  //
  I2C_SendData(0x6A);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_SendData(0x06);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  //
  I2C_SendData(0x6C);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_SendData(0x5b);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  //
  I2C_SendData(0x6E);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_SendData(0x4f);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  //TM1650_Set(0x68, 0x66);  /* Digit 1 */
  //TM1650_Set(0x6A, 0x6d);  /* Digit 2 */
  //TM1650_Set(0x6C, 0x6d);  /* Digit 3 */
  //TM1650_Set(0x6E, 0x7f);  /* Digit 4 */
  
  I2C_GenerateSTOP(ENABLE);
  
  while (1){
    /*
    DHT_ReadAll(ptr);
    
    memcpy(data, &ptr[0], 5); 
    humid = (data[1] << 7) | data[0];
    temp = (data[3] << 7) | data[2];
    sum = data[0] + data[1] + data[2] + data[3];
    
    delay_ms(1000);
    */
  }
}

static void CLK_Config(void){
  CLK_DeInit();
  /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  /* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

static void TIM2_Config(void)
{
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_16, 0xFFFF);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

static void TM1650_Set(uint8_t address, uint8_t data)
{
  I2C_SendData(address);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_SendData(data);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line){ 
  while (1){}
}
#endif

