#ifndef __CONFIG_H
#define __CONFIG_H

/* Define value */
#define TIM4_PERIOD   124
#define MULTI         3600
#define ON            1
#define OFF           0

/* Define pin */
#define RELAY_1_PORT  GPIOD
#define RELAY_1_PIN   GPIO_PIN_4

#define RELAY_2_PORT  GPIOD
#define RELAY_2_PIN   GPIO_PIN_5

#define LED_1_PORT    GPIOD
#define LED_1_PIN     GPIO_PIN_3

#define LED_2_PORT    GPIOD
#define LED_2_PIN     GPIO_PIN_2

#define LED_3_PORT    GPIOC
#define LED_3_PIN     GPIO_PIN_7

#define LED_4_PORT    GPIOC
#define LED_4_PIN     GPIO_PIN_6

#define LED_5_PORT    GPIOC
#define LED_5_PIN     GPIO_PIN_5

#define CMD_D_PORT    GPIOB
#define CMD_D_PIN     GPIO_PIN_5

#define CMD_C_PORT    GPIOB
#define CMD_C_PIN     GPIO_PIN_4

#define CMD_B_PORT    GPIOC
#define CMD_B_PIN     GPIO_PIN_3

#define CMD_A_PORT    GPIOC
#define CMD_A_PIN     GPIO_PIN_4

#endif
