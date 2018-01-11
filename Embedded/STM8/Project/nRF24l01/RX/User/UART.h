#ifndef __UART_H_
#define __UART_H_

#include <iostm8.h>
#include "lt_stm8s_macro.h"

void Init(void);
uint8_t getData(void);
void sendData(uint8_t data);

static struct{
	void (*Init)(void);
	uint8_t (*getData)(void);
	void (*sendData)(uint8_t data);
} UART = 
{
  Init,
  getData,
  sendData
};

#endif
