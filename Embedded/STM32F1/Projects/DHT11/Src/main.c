/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "init.h"
#include "onewire.h"
#include "DHT11.h"
#include <string.h>

/* Variables */
uint8_t data[5];
uint16_t temp = 0;
uint16_t humid = 0;
uint16_t sum = 0;

int main(void)
{
  /* Configure the system clock */
  SystemClock_Config();
  GPIO_Config();
  Timer2_Config();
    
  OneWire_Init(GPIOB, GPIO_PIN_5);
 
  uint8_t *ptr = calloc(5, sizeof(uint8_t));
  
  while(1)
  {
    HAL_Delay(3000);

    DHT_ReadAll(ptr);
    memcpy(data, &ptr[0], 5); 
    humid = (data[1] << 7) | data[0];
    temp = (data[3] << 7) | data[2];
    sum = data[0] + data[1] + data[2] + data[3];
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while(1) 
  {/* USER CODE END Error_Handler */
    
  } 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
