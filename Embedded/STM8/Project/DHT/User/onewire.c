#include "onewire.h"

void wire_high(){
  GPIO_WriteHigh(OneWire_PORT, OneWire_PIN);
}

void wire_low(){
  GPIO_WriteLow(OneWire_PORT, OneWire_PIN);
}

void wire_input(){
  GPIO_Init(OneWire_PORT, OneWire_PIN, GPIO_MODE_IN_PU_NO_IT);
}

void wire_output(){
  GPIO_Init(OneWire_PORT, OneWire_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}
  
uint8_t wire_read(){
  uint8_t return_value = 0;
  
  if(GPIO_ReadInputPin(OneWire_PORT, OneWire_PIN)){
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
