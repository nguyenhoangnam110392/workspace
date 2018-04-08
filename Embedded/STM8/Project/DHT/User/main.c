#include "main.h"

void CLK_Config(void);
void TIM2_Config(void);
void TIM1_Config(void);
void I2C_Config(void);
void RotaryEncoder_Config(void);



/* Counter */
uint16_t counter = 0;
/* Variable LCD */
uint8_t displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
uint8_t displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
uint8_t displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

uint8_t backlight = LCD_BACKLIGHT;
uint8_t status = NOT_READY;
uint8_t mode = OPERATING_MODE;
uint8_t enter_setting = NOT_ENTER_SETTING;
uint8_t mode_index = 0;
uint8_t out_of_timer_is_set = YES;

uint8_t temp = 0;
uint8_t humid = 0;
uint16_t timer = 0;
uint8_t set_temp = 35;
uint8_t set_humid = 60;
uint16_t set_timer = 0;

void main(void){
  /* Variable */
  uint8_t *ptr = calloc(5, sizeof(uint8_t));
  counter = 9;
  
  /* Initialize configuration */
  CLK_Config();
  TIM2_Config();
  TIM1_Config();
  I2C_Config();
  LCD_Config();
  RotaryEncoder_Config();
  /* Enable interrupt*/
  enableInterrupts();
  
  delay_ms(500);

  while (1){
    if(mode == OPERATING_MODE)
    {
      /* Variables */
      uint8_t data[5] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF};
      uint8_t sum = 0;
      
      DHT_ReadAll(ptr);
      delay_ms(1000);
      memcpy(data, &ptr[0], 5); 
      humid = (data[1] << 7) | data[0];
      temp = (data[3] << 7) | data[2];
      sum = data[0] + data[1] + data[2] + data[3];
      if(status == NOT_READY && sum != 0 && mode == OPERATING_MODE)
      {
        LCD_send_command(LCD_CLEARDISPLAY);
        LCD_print_notification();
        status = READY;
      }
      
      if(status == READY && sum != 0 && (sum == humid + temp) && mode == OPERATING_MODE)
      {
        LCD_print_data(humid, temp, timer);
      }
      
      if(status == READY && timer > 0 && mode == OPERATING_MODE)
      {
        out_of_timer_is_set = NO;
        /* Temperature control */
        if(temp <= (set_temp - 1))
        {
          GPIO_WriteHigh(GPIOD, GPIO_PIN_4); /* Turn Heat device relay on */
        }
        else if(temp >= (set_temp + 1))
        {
          GPIO_WriteLow(GPIOD, GPIO_PIN_4); /* Turn Heat device relay off */
        }
        
        /* Humid control */
        if(humid <= (set_humid - 1))
        {
          GPIO_WriteHigh(GPIOD, GPIO_PIN_5); /* Turn Humid device relay on */
        }
        else if(humid >= (set_humid + 1))
        {
          GPIO_WriteLow(GPIOD, GPIO_PIN_5); /* Turn Humid device relay off */
        }
        
        /* Interrupt setting off */
        TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
      }
      else if(status == READY && timer == 0 && mode == OPERATING_MODE)
      {
        if(out_of_timer_is_set == NO)
        {
          out_of_timer_is_set = YES;
          /* Interrupt setting off */
          TIM1_ITConfig(TIM1_IT_UPDATE, DISABLE);
          /* Turn Humid device relay off */
          GPIO_WriteLow(GPIOD, GPIO_PIN_5);
          /* Turn Heat device relay off */
          GPIO_WriteLow(GPIOD, GPIO_PIN_4);
          
          delay_ms(100);
          /* Message : Clear 2nd row  */
          uint8_t tmp_clear[9] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
          LCD_setCursor(1, 5);
          for(int i=0; i<sizeof(tmp_clear); i++)
          {
            LCD_send_char(tmp_clear[i]);
          }
          
          /* Message :             i     s  [SPACE]  o     f     f                    */
          uint8_t tmp_reset[6] = {0x69, 0x73, 0x20, 0x6F, 0x66, 0x66};
          LCD_setCursor(1, 6);
          for(int i=0; i<sizeof(tmp_reset); i++)
          {
            LCD_send_char(tmp_reset[i]);
          }
        }
      }
    }
  }
}

void CLK_Config(void){
  CLK_DeInit();
  /* Configure the Fcpu to DIV1*/
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  /* Configure the HSI prescaler to the optimal value */
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  /* Configure the system clock to use HSI (High Speed Internal) clock source and to run at 16Mhz */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void TIM1_Config(void)
{
  TIM1_DeInit();
  /* Time base configuration - Prescaler: 64,000 -> 250 ticks/sec. Overflow: 250 */
  TIM1_TimeBaseInit(0xFA00, TIM1_COUNTERMODE_UP, 0xF9, 0);
  
  /* Clear timer flag */
  TIM1_ClearFlag(TIM1_FLAG_UPDATE);
  
  /* Interrupt setting off */
  TIM1_ITConfig(TIM1_IT_UPDATE, DISABLE);
  
  /* TIM2 enable counter */
  TIM1_Cmd(ENABLE);
}

void TIM2_Config(void)
{
  TIM2_DeInit();
  /* Time base configuration 1,000,000 clock per second */
  TIM2_TimeBaseInit(TIM2_PRESCALER_16, 0xFFFF);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

void I2C_Config(void)
{
  I2C_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,ENABLE);
  I2C_Cmd(ENABLE);
  I2C_Init(10000, 0x00, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
}

void RotaryEncoder_Config(void)
{
  /* Initialize A pin */
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);
  /* Initialize B pin */
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
  /* Initialize SW pin */
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_IT);
  /* Set interrupt on PORTD */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
  /* Set interrupt on PORTD */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  
  /* Initialize Relay 1 pin */
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_SLOW);
  /* Initialize Relay 2 pin */
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_SLOW);
  /* Set default value */
  GPIO_WriteLow(GPIOD, GPIO_PIN_4);
  GPIO_WriteLow(GPIOD, GPIO_PIN_5);
}
void LCD_Config(void)
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

void LCD_backlight_mode(uint8_t state)
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

void LCD_display_mode(uint8_t state)
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

void LCD_print_data(uint8_t humid_data, uint8_t temp_data, uint8_t temp_timer)
{
  uint8_t hex[2];

  /* Print humid */
  hex[0] = humid_data / 10 + 48;
  hex[1] = humid_data % 10 + 48;

  LCD_setCursor(0, 8);
  LCD_send_char(hex[0]);
  LCD_send_char(hex[1]);

  /* Print temperature */
  hex[0] = temp_data / 10 + 48;
  hex[1] = temp_data % 10 + 48;

  LCD_setCursor(0, 12);
  LCD_send_char(hex[0]);
  LCD_send_char(hex[1]);
  
  if(temp_timer > 0)
  {
    /* Print timer */
    hex[0] = temp_timer / 10 + 48;
    hex[1] = temp_timer % 10 + 48;

    LCD_setCursor(1, 7);
    LCD_send_char(hex[0]);
    LCD_send_char(hex[1]);
  }
}

void LCD_print_notification(void)
{
  /* Message :               S      t     a     t     u     s     :  [SPACE] '8'  '9'   %     -    '12'  '13'   '     C*/
  uint8_t tmp_status[16] = {0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3A, 0x20, 0x5F, 0x5F, 0x25, 0x2D, 0x5F, 0x5F, 0x27, 0x43}; 
  LCD_setCursor(0, 0);
  for(int i=0; i<sizeof(tmp_status); i++)
  {
    LCD_send_char(tmp_status[i]);
  }
  
  if(timer == 0)
  {
    /* Message :               T    i     m     e     r [SPACE]    i     s  [SPACE]  o     f     f   */
    uint8_t tmp_timer[12] = {0x54, 0x69, 0x6D, 0x65, 0x72, 0x20, 0x69, 0x73, 0x20, 0x6F, 0x66, 0x66};
    LCD_setCursor(1, 0);
    for(int i=0; i<sizeof(tmp_timer); i++)
    {
      LCD_send_char(tmp_timer[i]);
    }
  }
  else
  {
    uint8_t hex[2];
    hex[0] = timer / 10 + 48;
    hex[1] = timer % 10 + 48;
    /* Message :               T    i     m     e     r      :  [SPACE]  7      8     [SPACE]  m     i     n    s */
    uint8_t tmp_timer[14] = {0x54, 0x69, 0x6D, 0x65, 0x72, 0x3A, 0x20, hex[0], hex[1], 0x20, 0x6D, 0x69, 0x6E, 0x73};
    LCD_setCursor(1, 0);
    for(int i=0; i<sizeof(tmp_timer); i++)
    {
      LCD_send_char(tmp_timer[i]);
    }
  }
}

void LCD_print_config_mode(uint8_t index)
{
  uint8_t hex[2];
  
  if(index == 1)
  {
    LCD_send_command(LCD_CLEARDISPLAY);
    hex[0] = set_temp / 10 + 48;
    hex[1] = set_temp % 10 + 48;
    /* Message :             >      T     e     m     p    :  [SPACE] '8'     '9'     '     C*/
    uint8_t tmp_temp[11] = {0x3E, 0x54, 0x65, 0x6D, 0x70, 0x3A, 0x20, hex[0], hex[1], 0x27, 0x43}; 
    LCD_setCursor(0, 0);
    for(int i=0; i<sizeof(tmp_temp); i++)
    {
      LCD_send_char(tmp_temp[i]);
    }
  
    hex[0] = set_humid / 10 + 48;
    hex[1] = set_humid % 10 + 48;
    
    /*Message :            [SPACE]  H     u     m     i      d    :  [SPACE]  '7'    '8'     %*/
    uint8_t tmp_humid[11] = {0x20, 0x48, 0x75, 0x6D, 0x69, 0x64, 0x3A, 0x20, hex[0], hex[1], 0x25};
    LCD_setCursor(1, 0);
    for(int i=0; i<sizeof(tmp_humid); i++)
    {
      LCD_send_char(tmp_humid[i]);
    }
  }
  else if(index == 2)
  {
    hex[0] = set_temp / 10 + 48;
    hex[1] = set_temp % 10 + 48;
    LCD_setCursor(0, 0);
    LCD_send_char(0x20); /* Add SPACE at the 1st position*/
  
    hex[0] = set_humid / 10 + 48;
    hex[1] = set_humid % 10 + 48;
    LCD_setCursor(1, 0);
    LCD_send_char(0x3E); /* Add > at the 1st position */
  }
  else if(index == 3)
  {
    LCD_send_command(LCD_CLEARDISPLAY);
    hex[0] = set_timer / 10 + 48;
    hex[1] = set_timer % 10 + 48;
    /* Message :               >    T    i     m     e     r      :  [SPACE]  '8'    '9'   [SPACE]  m     i     n   */
    uint8_t tmp_timer[14] = {0x3E, 0x54, 0x69, 0x6D, 0x65, 0x72, 0x3A, 0x20, hex[0], hex[1], 0x20, 0x6D, 0x69, 0x6E};
    LCD_setCursor(0, 0);
    for(int i=0; i<sizeof(tmp_timer); i++)
    {
      LCD_send_char(tmp_timer[i]);
    }
    
    /* Message :          [SPACE]  E     x    i     t  */
    uint8_t tmp_exit[5] = {0x20, 0x45, 0x78, 0x69, 0x74};
    LCD_setCursor(1, 0);
    for(int i=0; i<sizeof(tmp_exit); i++)
    {
      LCD_send_char(tmp_exit[i]);
    }
  }
  else if(index == 4)
  {
    hex[0] = set_timer / 10 + 48;
    hex[1] = set_timer % 10 + 48;
    
    timer = set_timer;

    LCD_setCursor(0, 0);
    LCD_send_char(0x20);
    
    LCD_setCursor(1, 0);
    LCD_send_char(0x3E);
  }
  else if(index >= 5)
  {
    mode_index = 0;
    mode = OPERATING_MODE;
    LCD_send_command(LCD_CLEARDISPLAY);
    status = NOT_READY;
    /* Message : Loading... */
    uint8_t tmp_loading[10] = {0x4C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x2E, 0x2E, 0x2E};
    LCD_setCursor(0, 0);
    for(int i=0; i<sizeof(tmp_loading); i++)
    {
      LCD_send_char(tmp_loading[i]);
    }
  }
}

void LCD_setCursor(uint8_t row, uint8_t col)
{
  uint8_t row_offsets[4] = {0x00, 0x40, 0x14, 0x54};
  LCD_send_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_Write4Bit(uint8_t data)
{
  LCD_Write_Bit(data);
  LCD_Write_Enable_Bit(data);
}

void LCD_send_command(uint8_t data)
{
  uint8_t highnib = data & 0xF0;
  uint8_t lownib = (data<<4) & 0xF0;
  LCD_Write4Bit(highnib);
  LCD_Write4Bit(lownib);
}

void LCD_send_char(uint8_t data)
{
  uint8_t highnib = data & 0xF0;
  uint8_t lownib = (data<<4) & 0xF0;
  LCD_Write4Bit(highnib | LCD_SELECT_BIT);
  LCD_Write4Bit(lownib | LCD_SELECT_BIT);
}

void LCD_Write_Enable_Bit(uint8_t data)
{
  LCD_Write_Bit(data | LCD_ENABLE_BIT);
  delay_us(2);
  
  LCD_Write_Bit(data | ~LCD_ENABLE_BIT);
  delay_us(50);
}

void LCD_Write_Bit(uint8_t data)
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

