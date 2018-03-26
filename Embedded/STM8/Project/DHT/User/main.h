#ifndef _MAIN_H_
#define _MAIN_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm8s.h"

#include "DHT11.h"
#include "delay.h"
#include "onewire.h"
#include "config.h"

void delay_us(uint16_t x);
void delay_ms(uint16_t x);

#endif

