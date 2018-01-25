/*============================================================================*/
/* Library      : eeprom.c                                                    */
/* Description  : Provide API to access EEPROM                                */
/* Device       : STM8                                                        */
/*============================================================================*/
/*                                COPYRIGHT                                   */
/*============================================================================*/
/* Copyright(c) 2018 nguyenhoangnam110392@gmail.com                           */
/*============================================================================*/
#ifndef __EEPROM_H_
#define __EEPROM_H_
/*******************************************************************************
**                             Include Section                                **
*******************************************************************************/
#include "main.h"
/*******************************************************************************
**                           API Declaration Section                          **
*******************************************************************************/
uint8_t EEPROM_Write_Value(void);
uint8_t VerifyEEPROMData(void);

#endif
/********************************END OF FILE***********************************/