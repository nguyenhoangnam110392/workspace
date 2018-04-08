#ifndef __MAIN__H__
#define __MAIN__H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm8s.h"

#include "DHT11.h"
#include "delay.h"
#include "config.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define LCD_ENABLE_BIT 0x04  // Enable bit
#define READ_WRITE_BIT 0x02  // Read/Write bit
#define LCD_SELECT_BIT 0x01 // Register select bit



void delay_us(uint16_t x);
void delay_ms(uint16_t x);
void LCD_send_command(uint8_t data);
void LCD_print_config_mode(uint8_t index);
void LCD_print_notification(void);
void LCD_setCursor(uint8_t col, uint8_t row);
void LCD_Config(void);
void LCD_backlight_mode(uint8_t state);
void LCD_display_mode(uint8_t state);
void LCD_print_data(uint8_t humid_data, uint8_t temp_data, uint8_t temp_timer);
void LCD_Write_Bit(uint8_t data);
void LCD_Write_Enable_Bit(uint8_t data);
void LCD_Write4Bit(uint8_t data);
void LCD_send_char(uint8_t data);

#endif

