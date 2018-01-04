#ifndef __CONFIG_H
#define __CONFIG_H

/* Define value */
#define TIM4_PERIOD   124
#define TEMP_HIGH     35.0
#define TEMP_LOW      30.0

/* Define pin */
#define LM35_PORT         GPIOD
#define LM35_PIN          GPIO_PIN_2

#define CHARGER_PORT      GPIOB
#define CHARGER_PIN       GPIO_PIN_4

#define RPI_PORT          GPIOB
#define RPI_PIN           GPIO_PIN_5

#define RPI_SIGNAL_PORT   GPIOA
#define RPI_SIGNAL_PIN    GPIO_PIN_3

#define TOUCH_PORT        GPIOA
#define TOUCH_PIN         GPIO_PIN_1

#endif
