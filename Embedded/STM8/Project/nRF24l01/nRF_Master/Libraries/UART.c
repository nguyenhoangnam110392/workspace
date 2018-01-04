#include "UART.h"

void Init(void){
  UART1_CR1 = 0X00;
  UART1_CR2 = 0X00;
  UART1_CR3 = 0X00;
  UART1_BRR2 = 0X0b; //Baud Rate 115200
  UART1_BRR1 = 0X08;       
  UART1_CR2 = 0X2c; 
}

void sendData(u8 data){
  while(!(UART1_SR & 0X80));
  UART1_DR = data;
  while(!(UART1_SR & 0X40));
}

void Create_sensorFeedback(data_typedef *data_frame, Sensor_TypeDef *sensor){
  u8 data[32];
  u8 subPayLoad[31];
  for(int i = 0; i<sizeof(data_frame->payLoad); i++){
    data_frame->payLoad[i] = 0;
  }
  
  data[0] = DataAddress.START_BIT_1; /* 0xAA */
  data[1] = DataAddress.START_BIT_2; /* 0xFF */
  data[2] = DataLength.Sensor + 2;   /* 0x07 */
  data[3] = DataAddress.Sensor;      /* 0x01 */
  data[4] = DataLength.Sensor;       /* 0x05 */
  data[5] = sensor->temperature_data;/* Temperature data 8 byte */
  data[6] = sensor->humid_data;      /* Humid data 8 byte */
  data[7] = sensor->light_data;      /* Light data 8 byte */
  data[8] = sensor->motion_data;     /* Motion data 8 byte */
  data[9] = sensor->current_data;    /* Current data 8 byte */
  
  u8 payLoadLength = DataLength.Control + 3;  /* 8 */
  memcpy(&subPayLoad[0], &data[2], payLoadLength);
  
  sensor->sum = checkSUM(subPayLoad, payLoadLength);  /* SUM */  
  data[10] = sensor->sum;
  
  memcpy(&data_frame->payLoad[0], &data[0], payLoadLength+3);  /* 11 */
}

void Create_controlDevice(data_typedef *data_frame, Control_TypeDef *control){
  u8 data[32];
  u8 subPayLoad[31];
  for(int i = 0; i<sizeof(data_frame->payLoad); i++){
    data_frame->payLoad[i] = 0;
  }
  
  data[0] = DataAddress.START_BIT_1;
  data[1] = DataAddress.START_BIT_2;
  data[2] = DataLength.Control + 2;
  data[3] = DataAddress.Control;
  data[4] = DataLength.Control;
  data[5] = control->command_1;      /* Command 1 0x00 is OFF, 0x01 is ON*/
  data[6] = control->command_2;      /* Command 2 0x00 is OFF, 0x01 is ON*/
  data[7] = control->command_3;      /* Command 3 0x00 is OFF, 0x01 is ON*/
  data[8] = control->command_4;      /* Command 4 0x00 is OFF, 0x01 is ON*/
  data[9] = control->command_5;      /* Command 5 0x00 is OFF, 0x01 is ON*/
  
  u8 payLoadLength = DataLength.Control + 3;
  memcpy(&subPayLoad[0], &data[2], payLoadLength);
  
  control->sum = checkSUM(subPayLoad, payLoadLength);  /* SUM */  
  data[10] = control->sum;
  
  memcpy(&data_frame->payLoad[0], &data[0], payLoadLength+3);
}

u8 checkSUM(u8 *array, u8 data_length){  
  u8 checksum = data_length;
  
  for (int i=0; i<sizeof(array); i++){
    checksum ^= array[i];
  }
  
  return checksum;
}
