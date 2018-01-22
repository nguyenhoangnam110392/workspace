/*
 *******************************************************************************
 * File: eeprom.c                                                              *
 * Function: Read/write EEPROM. Use for STM8S103                               *
 * Parameter: None                                                             *
 * Returns: None                                                               *
 * Description: None                                                           *
 *******************************************************************************
 */

#include "eeprom.h"

/* Data to write into the EEPROM */
static uint8_t data[9] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
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
  uint8_t status;
  status = FLASH->IAPSR & FLASH_FLAG_DUL;
  /* Check if the EEPROM is write-protected. If it is then unlock the EEPROM */
  if (status == 0)
  {
    FLASH->DUKR = 0xAE;     /* Warning: keys are reversed on data memory !!! */
    FLASH->DUKR = 0x56;
  }

  /* Write the data to the EEPROM. */
  uint8_t *address = (uint8_t*) EEPROM_ADDRESS + 7;  /*  EEPROM base address */
  /*  Store number of data */
  *address = 0x07;
  //for (uint8_t index = 0; index < 7; index++)
  //{
      *address++ = data[0];
      *address++ = data[1];
      *address++ = data[2];
      *address++ = data[3];
  //}
  /* Now write protect the EEPROM */
  FLASH->IAPSR = ~FLASH_IAPSR_DUL;
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
    for (int index = 0; index < 8; index++)
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