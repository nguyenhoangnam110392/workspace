#include "onewire.h"
#include "DHT11.h"
#include <string.h>

/* Local function */
uint8_t DHT_ReadByte();

/* Declear variables */
extern TIM_HandleTypeDef htim2;
uint16_t LocalData[40];
uint8_t DHT_data[5];

/* -------------------------------------------------------------------------- */
void DHT_ReadAll(uint8_t *pointer) {
  /* Local variable */
  uint8_t return_value = ONEWIRE_OK;
  
  /* Change to output mode */
  wire_output();        HAL_Delay(1);
  
  /* Reset one wire connection : pull high */
  wire_high();          HAL_Delay(1);
  
  /* Send request : pull low > 20ms */
  wire_low();           HAL_Delay(1);
  
  /* End request : pull high again > 20ms */
  wire_high();          //delay_us(5);
  
  /* Change to input mode */
  wire_input();
  
  /* Wait for DHT 11 response "low" signal */
  return_value = wait_low();
  
  /* Is low signal received? */
  if(return_value == ONEWIRE_OK){
    /* Wait for DHT 11 response "high" signal */
    return_value = wait_high();
  }
  
  /* Start receiving data */
  if(return_value == ONEWIRE_OK){
    /* Start reading data */
    return_value = DHT_ReadByte();
  }
  
  /* Data processing */
  if(return_value == ONEWIRE_OK){
    memcpy(pointer, &DHT_data[0], 5);
  }
}

uint8_t DHT_ReadByte(){
  uint8_t forty_bit = 40;
  uint8_t received_bit = 0;
  uint8_t return_value = ONEWIRE_OK;
  uint16_t time_stamp[2] = {0, 0};
  uint8_t index = 0;
  
  /* Wait for start-to-transmitt bit : low signal */
  return_value = wait_low();
  
  while (forty_bit--) {
    if(return_value == ONEWIRE_OK){
      /* Wait for high bit data */
      return_value = wait_high();
      /* Log the time when hit high signal */
      time_stamp[0] = htim2.Instance->CNT; 
    }
    
    if(return_value == ONEWIRE_OK){
      /* Wait until one bit is given: low */
      return_value = wait_low();
      /* Log the time when hit low signal */
      time_stamp[1] = htim2.Instance->CNT;
      
      int32_t diff = time_stamp[1] - time_stamp[0];
      if(diff > 0 && diff < 100){
        LocalData[index++] = diff;
      }
      else if (diff < 0){
        LocalData[index++] = 65536 + diff;
      }
      else{
        return_value = ONEWIRE_NOT_OK;
      }
    }
  }

  /* Transform data from 40 items to five 8-bit numbers */
  /* Check if data read enough 40 items or not */
  /* If not, return ONEWIRE_NOT_OK */
  if(index != 40 && return_value == ONEWIRE_OK){
    return_value = ONEWIRE_NOT_OK;
  }
  /* Read enough 40 items */
  else if(index == 40 && return_value == ONEWIRE_OK) {
    /* Index for data array. There are 5 corresponding items */
    int8_t idx = -1;
    /* Scan each item in list. If time_stamp 20~28 -> low bit */
    /* Otherwise, time_stamp 50~70 -> high bit */
    for(int i=0; i<40; i++){
      /* Low bit is detected */
      if(LocalData[i] > 0 && LocalData[i] < 30){
        received_bit = 0;
      }
      /* High bit is detected */
      else if(LocalData[i] > 30 && LocalData[i] < 80){
        received_bit = 1;
      }
      /* Break each 8 bits to create 1 byte */
      if((i % 8) == 0)   {   idx++;  }
      /* Move data into byte */
      /* Shift all bit to the left, and merge with received bit 
      on the right */
      DHT_data[idx] <<= 1;
      DHT_data[idx] |= received_bit;
    }
  }

  return return_value;
}
