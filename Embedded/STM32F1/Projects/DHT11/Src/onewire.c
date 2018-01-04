#include "onewire.h"
#include "init.h"
#include <string.h>

/* Declear variables */
OneWire_t onewire;
extern TIM_HandleTypeDef htim2;

/* -------------------------------------------------------------------------- */
void OneWire_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
  /* Save settings */
  onewire.GPIOx = GPIOx;
  onewire.GPIO_Pin = GPIO_Pin;
}

void wire_high(){
  HAL_GPIO_WritePin(onewire.GPIOx, onewire.GPIO_Pin, GPIO_PIN_SET);
}

void wire_low(){
  HAL_GPIO_WritePin(onewire.GPIOx, onewire.GPIO_Pin, GPIO_PIN_RESET);
}

void wire_input(){
  GPIO_Init(onewire.GPIOx, onewire.GPIO_Pin, GPIO_MODE_INPUT, 
                                            GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
}

void wire_output(){
  GPIO_Init(onewire.GPIOx, onewire.GPIO_Pin, GPIO_MODE_OUTPUT_PP, 
                                            GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
}
  
uint8_t wire_read(){
  uint8_t return_value = 0;
  
  if(HAL_GPIO_ReadPin(onewire.GPIOx, onewire.GPIO_Pin)){
    return_value = 1;
  }
  else{
    return_value = 0;
  }
  
  return return_value;
}

uint8_t wait_high(){
  /* System status */
  uint8_t return_value = ONEWIRE_OK;
  
  /* Wait for DHT 11 response "high" signal */
  uint32_t timeout = 0xFFFF;
  while(!wire_read() && (timeout--));
  
  /* Check timeout */
  if(timeout == 0){
    return_value = ONEWIRE_NOT_OK;
  }
  
  return return_value;
}

uint8_t wait_low(){
  uint8_t return_value = ONEWIRE_OK;
  
  /* Wait for DHT 11 response "low" signal */
  uint32_t timeout = 0xFFFF;
  while(wire_read() && (timeout--));
  
  /* Check timeout */
  if(timeout == 0){
    return_value = ONEWIRE_NOT_OK;
  }
  
  return return_value;
}
