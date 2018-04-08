#ifndef _CONFIG_
#define _CONFIG_

#define I2C_SPEED    400000
#define OneWire_PORT GPIOA
#define OneWire_PIN  GPIO_PIN_2

#define READY 0x00
#define NOT_READY 0x01

#define OPERATING_MODE 0x00
#define CONFIG_MODE 0x01

#define ENTER_SETTING 0x00
#define NOT_ENTER_SETTING 0x01

#define NO 0x00
#define YES 0x01

#endif

