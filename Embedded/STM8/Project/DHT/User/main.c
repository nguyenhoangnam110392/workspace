#include "main.h"

static void CLK_Config(void);
static void TIM2_Config(void);
static void I2C_Config(void);
static void LCD_Config(void);
static void LCD_backlight_mode(uint8_t state);
static void LCD_display_mode(uint8_t state);
static void LCD_print_data(uint8_t humid_data, uint8_t temp_data);
static void LCD_print_notification(void);
static void LCD_Write_Bit(uint8_t data);
static void LCD_Write_Enable_Bit(uint8_t data);
static void LCD_Write4Bit(uint8_t data);
static void LCD_send_command(uint8_t data);
static void LCD_send_char(uint8_t data);
static void LCD_setCursor(uint8_t col, uint8_t row);

/* Counter */
uint16_t counter = 0;
/* Variable LCD */
uint8_t displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
uint8_t displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
uint8_t displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
uint8_t backlight = LCD_BACKLIGHT;
uint8_t status = NOT_READY;

void main(void){
  /* Variable */
  uint8_t *ptr = calloc(5, sizeof(uint8_t));
  counter = 9;
  /* Initialize configuration */
  CLK_Config();
  I2C_Config();
  LCD_Config();
  TIM2_Config();
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  enableInterrupts();
  
  LCD_send_command(LCD_CLEARDISPLAY);
  while (1){
    /* Variables */
    uint8_t data[5] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF};
    uint16_t temp = 0;
    uint16_t humid = 0;
    uint16_t sum = 0;
    
    DHT_ReadAll(ptr);
    
    memcpy(data, &ptr[0], 5); 
    humid = (data[1] << 7) | data[0];
    temp = (data[3] << 7) | data[2];
    sum = data[0] + data[1] + data[2] + data[3];
    if((sum != 0) && (status == NOT_READY))
    {
      LCD_print_notification();
      status = READY;
    }
    
    if((sum == humid + temp) && (status == READY))
    {
      LCD_print_data(humid, temp);
    }
    delay_ms(1000);
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

static void I2C_Config(void)
{
  I2C_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,ENABLE);
  I2C_Cmd(ENABLE);
  I2C_Init(10000, 0x00, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
}

static void LCD_Config(void)
{
  /* Set 4 bits mode - 1st try */
  LCD_Write4Bit(0x03 << 4);
  delay_ms(50);

  /* Set 4 bits mode - 2nd try */
  LCD_Write4Bit(0x03 << 4);
  delay_ms(50);

 /* Set 4 bits mode - 3rd try */
  LCD_Write4Bit(0x03 << 4);
  delay_ms(20);

  /* Finally, set to 4-bit interface */
  LCD_Write4Bit(0x02 << 4);

  /* Set # lines, font size, etc */
  LCD_send_command(LCD_FUNCTIONSET | displayfunction);
  
  /* Set entry mode */
  LCD_send_command(LCD_ENTRYMODESET | displaymode);
  
  /* Set display control - important */
  LCD_send_command(LCD_DISPLAYCONTROL | displaycontrol);
  
  /* Clear display */
  LCD_send_command(LCD_CLEARDISPLAY);
  
  /* Return home */
  LCD_send_command(LCD_RETURNHOME);
  delay_ms(500);
  
  /* Setting is done. Print "Initializing..." message to test */
  uint8_t tmp_data[15] = {0x49, 0x6E, 0x69, 0x74, 0x69, 0x61, 0x6C, 0x69, 0x7A, 0x69, 0x6E, 0x67, 0x2E, 0x2E, 0x2E};

  for(int i=0; i<sizeof(tmp_data); i++)
  {
    LCD_send_char(tmp_data[i]);
  }
  /* Delay displaying message */
  delay_ms(1000);
}

static void LCD_backlight_mode(uint8_t state)
{
  if(state == LCD_BACKLIGHT)
  {
    backlight = LCD_BACKLIGHT;
    LCD_Write_Bit(0);
  }
  else
  {
    backlight = LCD_NOBACKLIGHT;
    LCD_Write_Bit(0);
  }
}

static void LCD_display_mode(uint8_t state)
{
  if(state == LCD_DISPLAYON)
  {
    displaycontrol |= LCD_DISPLAYON;
    LCD_send_command(LCD_DISPLAYCONTROL | displaycontrol);
  }
  else
  {
    displaycontrol |= LCD_DISPLAYOFF;
    LCD_send_command(LCD_DISPLAYCONTROL | displaycontrol);
  }
}

static void LCD_print_data(uint8_t humid_data, uint8_t temp_data)
{
  uint8_t hex[2];

  hex[0] = humid_data / 10 + 48;
  hex[1] = humid_data % 10 + 48;

  LCD_setCursor(0, 8);
  LCD_send_char(hex[0]);
  LCD_send_char(hex[1]);

  hex[0] = temp_data / 10 + 48;
  hex[1] = temp_data % 10 + 48;

  LCD_setCursor(0, 12);
  LCD_send_char(hex[0]);
  LCD_send_char(hex[1]);
}

static void LCD_print_notification(void)
{
  /* Message :               S      t     a     t     u     s     :  [SPACE] '8'  '9'   %     -    '12'  '13'   '     C*/
  uint8_t tmp_status[16] = {0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3A, 0x20, 0x5F, 0x5F, 0x25, 0x2D, 0x5F, 0x5F, 0x27, 0x43}; 
  LCD_setCursor(0, 0);
  for(int i=0; i<sizeof(tmp_status); i++)
  {
    LCD_send_char(tmp_status[i]);
  }
  
  /*Message :                T      i     m     e     r [SPACE]  i     s  [SPACE]  o     f     f*/
  uint8_t tmp_timer[12] = {0x54, 0x69, 0x6D, 0x65, 0x72, 0x20, 0x69, 0x73, 0x20, 0x6F, 0x66, 0x66};
  LCD_setCursor(1, 0);
  for(int i=0; i<sizeof(tmp_timer); i++)
  {
    LCD_send_char(tmp_timer[i]);
  }
}

static void LCD_setCursor(uint8_t row, uint8_t col)
{
  uint8_t row_offsets[4] = {0x00, 0x40, 0x14, 0x54};
  LCD_send_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

static void LCD_Write4Bit(uint8_t data)
{
  LCD_Write_Bit(data);
  LCD_Write_Enable_Bit(data);
}

static void LCD_send_command(uint8_t data)
{
  uint8_t highnib = data & 0xF0;
  uint8_t lownib = (data<<4) & 0xF0;
  LCD_Write4Bit(highnib);
  LCD_Write4Bit(lownib);
}

static void LCD_send_char(uint8_t data)
{
  uint8_t highnib = data & 0xF0;
  uint8_t lownib = (data<<4) & 0xF0;
  LCD_Write4Bit(highnib | LCD_SELECT_BIT);
  LCD_Write4Bit(lownib | LCD_SELECT_BIT);
}

static void LCD_Write_Enable_Bit(uint8_t data)
{
  LCD_Write_Bit(data | LCD_ENABLE_BIT);
  delay_us(2);
  
  LCD_Write_Bit(data | ~LCD_ENABLE_BIT);
  delay_us(50);
}

static void LCD_Write_Bit(uint8_t data)
{
  while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY));

  I2C_GenerateSTART(ENABLE);
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(0x7E, I2C_DIRECTION_TX);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
        
  I2C_SendData(data | backlight);
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  
  I2C_GenerateSTOP(ENABLE);
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line){ 
  while (1){}
}
#endif

