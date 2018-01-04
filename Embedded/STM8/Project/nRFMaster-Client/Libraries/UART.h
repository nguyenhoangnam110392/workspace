#ifndef __UART_H_
#define __UART_H_

#include "main.h"

/* define data address */
static const struct{
  const u8 START_BIT_1;
  const u8 START_BIT_2;
  const u8 Sensor;
  const u8 Control;
}DataAddress =
{
  0xAA, 0xFF, 1, 2
};

/* define data length */
static const struct{
  const u8 Sensor;
  const u8 Control;
}DataLength =
{
  5, 5
};

/* define data array*/
static const struct{
  const u8 data_length;
  const u8 relay_1;
  const u8 relay_2;
  const u8 relay_3;
  const u8 relay_4;
  const u8 relay_5;
  const u8 command_1;
  const u8 command_2;
  const u8 command_3;
  const u8 command_4;
  const u8 command_5;
  const u8 sum;
}DataArray =
{
  4, 5, 6, 7, 8, 9 ,5, 6, 7, 8, 9, 10
};

/* define sensor frame */
typedef struct{
  u8 data_relay_1;
  u8 data_relay_2;
  u8 data_relay_3;
  u8 data_relay_4;
  u8 data_relay_5;
}Sensor_TypeDef;

/* define control frame */
typedef struct{
  u8 command_1;
  u8 command_2;
  u8 command_3;
  u8 command_4;
  u8 command_5;
}Control_TypeDef;

/* define payload frame */
typedef struct{
  u8 payLoad[32];
}data_typedef;


void Init(void);
void sendData(u8 data);
void Create_sensorFeedback(data_typedef *data_frame, Sensor_TypeDef *sensor);
void Create_controlDevice(data_typedef *data_frame, Control_TypeDef *control);
u8 checkSUM(u8 *array, u8 data_length);
u8 isPacketValid(u8 *array);

static struct{
  void (*Init)(void);
  void (*sendData)(u8 data);
  void (*Create_sensorFeedback)(data_typedef *data_frame, Sensor_TypeDef *sensor);
  void (*Create_controlDevice)(data_typedef *data_frame, Control_TypeDef *control);
  u8 (*checkSUM)(u8 *array, u8 data_length);
  u8 (*isPacketValid)(u8 *array);
} UART = 
{
  Init,
  sendData,
  Create_sensorFeedback,
  Create_controlDevice,
  checkSUM,
  isPacketValid
};




#endif
