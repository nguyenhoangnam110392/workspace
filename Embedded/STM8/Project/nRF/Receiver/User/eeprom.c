/**
  ******************************************************************************
  * File: eeprom.c                                                             *
  * Function: Read/write EEPROM. Use for STM8S103                              *
  * Parameter: None                                                            *
  * Returns: None                                                              *
  * Description: None                                                          *
  ******************************************************************************
  */

#include "eeprom.h"

/* Data to write into the EEPROM */
uint8_t data[7] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
#define EEPROM_ADDRESS    0x4000
#define EEPROM_FAILED     0x00
#define EEPROM_OK         0x01

/*******************************************************************************
 * Name: EEPROM_Write_Value
 * Function: Write data to EEPROM
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
void EEPROM_Write_Value(void)
{
  /* Check if the EEPROM is write-protected. If it is then unlock the EEPROM */
  if (FLASH_IAPSR_DUL == 0)
  {
    FLASH_PUKR_PUK = 0xAE;
    FLASH_PUKR_PUK = 0x56;
  }

  /* Write the data to the EEPROM. */
  uint8_t *address = (uint8_t*) EEPROM_ADDRESS;  /*  EEPROM base address */
  *address++ = 7;                                /*  Store number of data */
  for (uint8_t index = 0; index < 7; index++)
  {
      *address++ = data[index];
  }
  /* Now write protect the EEPROM */
  FLASH_IAPSR_DUL = 0;
}

/*******************************************************************************
 * Name: VerifyEEPROMData
 * Function: Write data to EEPROM
 * Parameter: None
 * Returns: None
 * Description: None
 ******************************************************************************/
uint8_t VerifyEEPROMData(void)
{
  uint8_t *address = (uint8_t*) EEPROM_ADDRESS;        //  EEPROM base address.
  uint8_t retVal = EEPROM_OK;

  if (*address++ != 7)
  {
    return EEPROM_FAILED;
  }
  else
  {
    for (int index = 0; index < 7; index++)
    {
      uint8_t value = *address++;
      if (value != data[index])
      {
        return EEPROM_FAILED;
      }
    }
  }
  return retVal;
}
/***************************** END OF FILE ***********************************/