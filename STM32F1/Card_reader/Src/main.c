/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "init.h"
#include "ff.h"
#include "diskio.h"
#include "stm32f1xx_hal_sd.h"

uint32_t timeTick = 0;

void delay(__IO uint32_t nTime);

HAL_SD_CardInfoTypedef SDCardInfo;
HAL_SD_CardStatusTypedef SDStatus;

/* Private function prototypes -----------------------------------------------*/
int main(void)
{
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  GPIO_Config();
  
  static FRESULT st_Result;   /* Result code */  
  static FATFS fatfs;  /* File system object */  
  static FIL fil;   /* File object */  
  static DIR dir;   /* Directory object */  
  static FILINFO fno;  /* File information object */  
  static UINT bw, br, numread;  
  
  BYTE Message[] = "MMC/SD : ICViet.vn d(^.=)b" ; // message's content  
  UCHAR *FilePath = "FILE test.TXT" ; // file path 	
  power();
  
  disk_initialize(0);
  BYTE res = disk_status(0);
  DRESULT result_read;
  numberOfFrame = SDCardInfo.CardCapacity / numberOfBlock;
  
  while (1)
  {
    
    

  }
}

void HAL_SYSTICK_Callback(void){
  timeTick++;
}

void delay(__IO uint32_t nTime){
  uint32_t current = timeTick;
  while((timeTick - current) < nTime);
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
