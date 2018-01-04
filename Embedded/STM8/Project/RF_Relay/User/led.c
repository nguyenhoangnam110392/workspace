/* Includes ------------------------------------------------------------------*/

#include "led.h"

void Start_up(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  Delay(40);   
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);  Delay(40);   
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);  Delay(40);   
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);  Delay(40);   
  GPIO_WriteHigh(LED_5_PORT, LED_5_PIN);  Delay(40);   
  
  GPIO_WriteLow(LED_1_PORT, LED_1_PIN);
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);
  GPIO_WriteHigh(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteLow(LED_1_PORT, LED_1_PIN);
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);
  GPIO_WriteHigh(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteLow(LED_1_PORT, LED_1_PIN);
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);
  GPIO_WriteHigh(LED_5_PORT, LED_5_PIN);
  
  Delay(100);
  
  GPIO_WriteLow(LED_1_PORT, LED_1_PIN);
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);
}

void LED_0(void){
  GPIO_WriteLow(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);  
}

void LED_1(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteLow(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);  
}

void LED_2(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteLow(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);  
}

void LED_3(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteLow(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);  
}

void LED_4(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteLow(LED_5_PORT, LED_5_PIN);  
}

void LED_5(void){
  GPIO_WriteHigh(LED_1_PORT, LED_1_PIN);  
  GPIO_WriteHigh(LED_2_PORT, LED_2_PIN);  
  GPIO_WriteHigh(LED_3_PORT, LED_3_PIN);    
  GPIO_WriteHigh(LED_4_PORT, LED_4_PIN);  
  GPIO_WriteHigh(LED_5_PORT, LED_5_PIN);  
}

void Relay(bool state){
  if(state){
    GPIO_WriteHigh(RELAY_1_PORT, RELAY_1_PIN);    /* Right */
    GPIO_WriteHigh(RELAY_2_PORT, RELAY_2_PIN);    /* Left */
  }
  else{
    GPIO_WriteLow(RELAY_1_PORT, RELAY_1_PIN);    /* Right */
    GPIO_WriteLow(RELAY_2_PORT, RELAY_2_PIN);    /* Left */
  }
}