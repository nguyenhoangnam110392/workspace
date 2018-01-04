#include "UART.h"

void Init(void){
  UART1_CR1  = 0X00;
  UART1_CR2  = 0X00;
  UART1_CR3  = 0X00;
  UART1_BRR2 = 0X0b; //Baud Rate 115200
  UART1_BRR1 = 0X08;       
  UART1_CR2  = 0X2c; 
}

void sendData(u8 data){
  while(!(UART1_SR & 0X80));
  UART1_DR = data;
  while(!(UART1_SR & 0X40));
}

void Create_sensorFeedback(data_typedef *data_frame, Sensor_TypeDef *sensor){
  u8 data[32];

  for(int i = 0; i<sizeof(data_frame->payLoad); i++){
    data_frame->payLoad[i] = 0;
  }
  
  data[0] = DataAddress.START_BIT_1; /* 0xAA */
  data[1] = DataAddress.START_BIT_2; /* 0xFF */
  data[2] = DataLength.Sensor + 2;   /* 0x07 */
  data[3] = DataAddress.Sensor;      /* 0x01 */
  data[DataArray.data_length] = DataLength.Sensor;      /* 0x05 */
  data[DataArray.relay_1] = sensor->data_relay_1;       /* Temperature data 8 byte */
  data[DataArray.relay_2] = sensor->data_relay_2;       /* Humid data 8 byte */
  data[DataArray.relay_3] = sensor->data_relay_3;       /* Light data 8 byte */
  data[DataArray.relay_4] = sensor->data_relay_4;       /* Motion data 8 byte */
  data[DataArray.relay_5] = sensor->data_relay_5;       /* Current data 8 byte */
  data[DataArray.sum] = checkSUM(&data[2], DataLength.Control + 3);  /* SUM */
  
  memcpy(&data_frame->payLoad[0], &data[0], DataLength.Control + 6);  /* 11 */
}

void Create_controlDevice(data_typedef *data_frame, Control_TypeDef *control){
  u8 data[32];

  for(int i = 0; i<sizeof(data_frame->payLoad); i++){
    data_frame->payLoad[i] = 0;
  }
  
  data[0] = DataAddress.START_BIT_1;
  data[1] = DataAddress.START_BIT_2;
  data[2] = DataLength.Control + 2;
  data[3] = DataAddress.Control;
  data[DataArray.data_length] = DataLength.Control;
  data[DataArray.command_1]   = control->command_1;      /* Command 1 0x00 is OFF, 0x01 is ON*/
  data[DataArray.command_2]   = control->command_2;      /* Command 2 0x00 is OFF, 0x01 is ON*/
  data[DataArray.command_3]   = control->command_3;      /* Command 3 0x00 is OFF, 0x01 is ON*/
  data[DataArray.command_4]   = control->command_4;      /* Command 4 0x00 is OFF, 0x01 is ON*/
  data[DataArray.command_5]   = control->command_5;      /* Command 5 0x00 is OFF, 0x01 is ON*/
  data[DataArray.sum] = checkSUM(&data[2], DataLength.Control + 3);  /* SUM */
  
  memcpy(&data_frame->payLoad[0], &data[0], DataLength.Control + 6);
}

u8 checkSUM(u8 *array, u8 data_length){  
  u8 checksum = data_length;
  
  for (int i=0; i<checksum; i++){
    checksum ^= array[i];
  }
  
  return checksum;
}

u8 isPacketValid(u8 *array){
  u8 checksum = array[DataArray.data_length] + 3;
  
  for (int i=2; i<checksum; i++){
    checksum ^= array[i];
  }
  
  if(array[DataArray.sum] == checksum){   return 1;  }
  
  return 0;   
}