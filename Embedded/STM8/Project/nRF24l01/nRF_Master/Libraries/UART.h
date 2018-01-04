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
/* define sensor frame */
typedef struct{
  u8 temperature_data;
  u8 humid_data;
  u8 light_data;
  u8 motion_data;
  u8 current_data;
  u8 sum;
}Sensor_TypeDef;


typedef struct{
  u8 command_1;
  u8 command_2;
  u8 command_3;
  u8 command_4;
  u8 command_5;
  u8 sum;
}Control_TypeDef;

typedef struct{
  u8 payLoad[32];
}data_typedef;


void Init(void);
void sendData(u8 data);
void Create_sensorFeedback(data_typedef *data_frame, Sensor_TypeDef *sensor);
void Create_controlDevice(data_typedef *data_frame, Control_TypeDef *control);
u8 checkSUM(u8 *array, u8 data_length);

static struct{
  void (*Init)(void);
  void (*sendData)(u8 data);
  void (*Create_sensorFeedback)(data_typedef *data_frame, Sensor_TypeDef *sensor);
  void (*Create_controlDevice)(data_typedef *data_frame, Control_TypeDef *control);
  u8 (*checkSUM)(u8 *array, u8 data_length);
} UART = 
{
  Init,
  sendData,
  Create_sensorFeedback,
  Create_controlDevice,
  checkSUM,
};




#endif
