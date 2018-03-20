#ifndef ONEWIRE_H
#define ONEWIRE_H 

#include "stm8s_gpio.h"

/* OneWire commands */
#define ONEWIRE_CMD_RSCRATCHPAD			0xBE
#define ONEWIRE_CMD_WSCRATCHPAD			0x4E
#define ONEWIRE_CMD_CPYSCRATCHPAD		0x48
#define ONEWIRE_CMD_RECEEPROM			0xB8
#define ONEWIRE_CMD_RPWRSUPPLY			0xB4
#define ONEWIRE_CMD_SEARCHROM			0xF0
#define ONEWIRE_CMD_READROM		        0x33
#define ONEWIRE_CMD_MATCHROM			0x55
#define ONEWIRE_CMD_SKIPROM			0xCC
#define ONEWIRE_OK                              0x01
#define ONEWIRE_NOT_OK                          0x00
#define SIGNAL_HIGH                             0x01
#define SIGNAL_LOW                              0x00

typedef struct {
  GPIO_TypeDef* GPIOx;          /*!< GPIOx port to be used for I/O functions */
  GPIO_Pin_TypeDef GPIO_Pin;    /*!< GPIO Pin to be used for I/O functions */
} OneWire_t;

void wire_high();
void wire_low();
void wire_output();
void wire_input();
uint8_t wire_read();
uint8_t wait_high();
uint8_t wait_low();
void OneWire_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin);

#endif

