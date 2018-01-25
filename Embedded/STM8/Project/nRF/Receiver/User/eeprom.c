/*============================================================================*/
/* Library      : eeprom.c                                                    */
/* Description  : Provide API to access EEPROM                                */
/* Device       : STM8                                                        */
/*============================================================================*/
/*                                COPYRIGHT                                   */
/*============================================================================*/
/* Copyright(c) 2018 nguyenhoangnam110392@gmail.com                           */
/*============================================================================*/

/*******************************************************************************
**                             Include Section                                **
*******************************************************************************/
#include "eeprom.h"
/*******************************************************************************
**                           Function Prototypes                              **
*******************************************************************************/
/*******************************************************************************
**                           Variable Definition                              **
*******************************************************************************/
#define EEPROM_FLAG_DUL       (uint8_t)0x08   /*< Data EEPROM unlocked flag > */
#define EEPROM_ADDRESS_START  0x4000          /*< EEPROM address start >      */
#define EEPROM_ADDRESS_END    0x427F          /*< EEPROM address start >      */
#define EEPROM_FAILED         0x01            /*< EEPROM return value >       */
#define EEPROM_OK             0x00            /*< EEPROM return value >       */
#define NUMBER_OF_DATA        0x07            /*< Number of array data >      */
/*******************************************************************************
**                           Variable Declaration                             **
*******************************************************************************/
  /*
  * Description: Data will be write to EEPROM
  * Bit 0: TX mode : 0 - RX mode : 1
  * Bit 1 to 5: Address of node
  * Bit 6: Checksum
  */
  uint8_t eeprom_data[NUMBER_OF_DATA] = {0};
/*******************************************************************************
 * Name: EEPROM_Write_Value
 * Function: Write data to EEPROM
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
uint8_t EEPROM_Write_Value(uint8_t *ptr)
{
  /* Copy pointed data to local array */
  memcpy(eeprom_data, ptr, NUMBER_OF_DATA);
  /* Check if the EEPROM is write-protected. If it is then unlock the EEPROM */
  if ((FLASH->IAPSR & EEPROM_FLAG_DUL) == 0)
  {
    FLASH->DUKR = 0xAE;     /* Write unlock key 1 */
    FLASH->DUKR = 0x56;     /* Write unlock key 2 */
  }

  /* Define pointer for EEPROM_ADDRESS */
  uint8_t *address = (uint8_t*) EEPROM_ADDRESS_START;
  /* Write data to EEPROM */
  for (uint8_t index = 0; index < NUMBER_OF_DATA; index++)
  {
    *address++ = eeprom_data[index];
  }
  /* Now write protect the EEPROM */
  FLASH->IAPSR = (uint8_t)(~EEPROM_FLAG_DUL);

  /* Verify written data in EEPROM */
  return VerifyEEPROMData(ptr);
}

/*******************************************************************************
 * Name: VerifyEEPROMData
 * Function: Write data to EEPROM
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
uint8_t VerifyEEPROMData(uint8_t *ptr)
{
  uint8_t retVal = EEPROM_OK;
  uint8_t original_data[NUMBER_OF_DATA] = {0};
  
  /* Copy pointed data to local array */
  memcpy(original_data, ptr, NUMBER_OF_DATA);

  /* Define pointer for EEPROM_ADDRESS */
  uint8_t *address = (uint8_t*) EEPROM_ADDRESS_START;
  for (int index = 0; index < NUMBER_OF_DATA; index++)
  {
    if (*address++ != original_data[index])
    {
      return EEPROM_FAILED;
    }
  }
  
  return retVal;
}
/****************************** END OF FILE ***********************************/