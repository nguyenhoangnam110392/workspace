/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "init.h"
#include "MPU6050.h"
#include <string.h>

/* Variables */

uint8_t retVal;

int main(void)
{
  /* Configure the system clock */
  SystemClock_Config();
  GPIO_Config();
  I2C1_Config();
  
  //retVal = MPU_OK;
  retVal = MPU6050_Init();
  
  while(1)
  {
  
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
