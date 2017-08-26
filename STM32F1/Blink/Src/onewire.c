/**	
 * |----------------------------------------------------------------------
 * | Copyright (c) 2016 Tilen Majerle
 * |  
 * | Permission is hereby granted, free of charge, to any person
 * | obtaining a copy of this software and associated documentation
 * | files (the "Software"), to deal in the Software without restriction,
 * | including without limitation the rights to use, copy, modify, merge,
 * | publish, distribute, sublicense, and/or sell copies of the Software, 
 * | and to permit persons to whom the Software is furnished to do so, 
 * | subject to the following conditions:
 * | 
 * | The above copyright notice and this permission notice shall be
 * | included in all copies or substantial portions of the Software.
 * | 
 * | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * | EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * | OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * | AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * | HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * | WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * | FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * | OTHER DEALINGS IN THE SOFTWARE.
 * |----------------------------------------------------------------------
 */
#include "onewire.h"
#include "delay.h"
#include "init.h"
#include <string.h>


void wire_high(OneWire_t* OneWireStruct);
void wire_low(OneWire_t* OneWireStruct);

void wire_output(OneWire_t* OneWireStruct);
uint8_t chip_response(OneWire_t* OneWireStruct);

uint8_t OneWire_ReadByte(OneWire_t* OneWireStruct);

/* -------------------------------------------------------------------------- */
void OneWire_Init(OneWire_t* OneWireStruct, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
  /* Save settings */
  OneWireStruct->GPIOx = GPIOx;
  OneWireStruct->GPIO_Pin = GPIO_Pin;
  /* Init pin for onewire */
  wire_output(OneWireStruct);
}

uint8_t chip_response(OneWire_t* OneWireStruct){
  /* Bit is LOW */
  uint32_t timeout = 0xFFFF;
  while(wire_read(OneWireStruct) && (timeout--));
  delay_us(40);
  
  timeout = 0xFFFF;
  while(!wire_read(OneWireStruct) && (timeout--));
  
  return 1;
}

void OneWire_ReadAll(OneWire_t* OneWireStruct, uint8_t *pointer) {
  /* Change to output */
  wire_output(OneWireStruct);
  delay_us(1000);
  
  /* Make sure one wire is reset*/
  wire_high(OneWireStruct);
  delay_us(250);
  
  /* First set data line low for 20 milliseconds */
  wire_low(OneWireStruct);
  delay_us(20);
  
  // End the start signal by setting data line high for 40 microseconds.
  wire_high(OneWireStruct);
  delay_us(40);
  
  // Now start reading the data line to get the value from the DHT sensor.
  wire_input(OneWireStruct);
  delay_us(10);
  
  //Copy to pointer
  uint8_t tmp_array[5]={0,0,0,0,0};
  if(chip_response(OneWireStruct)){
    uint8_t c = 3;
    while(c--){
      tmp_array[c] = OneWire_ReadByte(OneWireStruct);
    }
    memcpy(pointer, &tmp_array[0], sizeof(tmp_array));
  }
  
}

uint8_t OneWire_ReadByte(OneWire_t* OneWireStruct) {
  uint8_t byte = 0;
  uint8_t i = 8;
  uint32_t timeout = 0xFFFF;
  
  /* Wait for signal*/
  while(wire_read(OneWireStruct) && (timeout--));
  delay_us(35);
  
  while (i--) {
    timeout = 0xFFFF;
    while(!wire_read(OneWireStruct) && (timeout--));
    delay_us(70);
    
    byte >>= 1;
    byte |= (wire_read(OneWireStruct) << 7);
    
    timeout = 0xFFFF;
    while(wire_read(OneWireStruct) && (timeout--));
    delay_us(10);
  }
  
  return byte;
}

void wire_high(OneWire_t* OneWireStruct){
  HAL_GPIO_WritePin(OneWireStruct->GPIOx, OneWireStruct->GPIO_Pin, GPIO_PIN_SET);
}

void wire_low(OneWire_t* OneWireStruct){
  HAL_GPIO_WritePin(OneWireStruct->GPIOx, OneWireStruct->GPIO_Pin, GPIO_PIN_RESET);
}

void wire_input(OneWire_t* OneWireStruct){
  GPIO_Init(OneWireStruct->GPIOx, OneWireStruct->GPIO_Pin, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
}

void wire_output(OneWire_t* OneWireStruct){
  GPIO_Init(OneWireStruct->GPIOx, OneWireStruct->GPIO_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
}
  
uint8_t wire_read(OneWire_t* OneWireStruct){
  if(HAL_GPIO_ReadPin(OneWireStruct->GPIOx, OneWireStruct->GPIO_Pin)){
    return 1;
  }
  else{
    return 0;
  }
}