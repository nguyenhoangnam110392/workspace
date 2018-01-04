#ifndef __UART_H_
#define __UART_H_

#include <iostm8.h>
#include "lt_stm8s_macro.h"

void Init(void);
u8 getData(void);
void sendData(u8 data);

static struct{
	void (*Init)(void);
	u8 (*getData)(void);
	void (*sendData)(u8 data);
} UART = 
{
  Init,
  getData,
  sendData
};

#endif
