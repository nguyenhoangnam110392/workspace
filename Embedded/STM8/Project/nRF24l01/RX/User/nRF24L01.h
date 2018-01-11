#ifndef __NRF24L01_H_
#define __NRF24L01_H_

#include <iostm8.h>
#include "lt_stm8s_macro.h"

/* Define SPI pins */
#define CE    PC_ODR_bit.ODR3  /* Mode change pin, (output) */
#define CSN   PC_ODR_bit.ODR6  /* Chip enable pin, (output to CSN, nRF24L01) */
#define IRQ   PA_IDR_bit.IDR3  /* Interrupt signal, from nRF24L01 (input) */
#define MISO  PC_IDR_bit.IDR5  /* Master In, Slave Out pin (input) */
#define MOSI  PC_ODR_bit.ODR7  /* Master Out, Slave In pin (output) */
#define SCK   PC_ODR_bit.ODR4  /* Serial Clock pin, (output) */
#define LED   PB_ODR_bit.ODR5  /* LED in STM8S board */

#define TX_ADR_WIDTH   5  
#define RX_ADR_WIDTH   5
#define TX_PLOAD_WIDTH 32  
#define RX_PLOAD_WIDTH 32

extern uint8_t sta;
#define RX_DR  (sta & 0x40)
#define TX_DS  (sta & 0x20)
#define MAX_RT (sta & 0x10)


/* SPI(nRF24L01) commands */
#define READ_REG    0x00  /* Define read command to register */
#define WRITE_REG   0x20  /* Define write command to register */
#define RD_RX_PLOAD 0x61  /* Define RX payload register address */
#define WR_TX_PLOAD 0xA0  /* Define TX payload register address */
#define FLUSH_TX    0xE1  /* Define flush TX register command */
#define FLUSH_RX    0xE2  /* Define flush RX register command */
#define REUSE_TX_PL 0xE3  /* Define reuse TX payload register command */
#define NOP         0xFF  /* Define No Operation, might be used to read status register */

/* SPI(nRF24L01) registers(addresses) */
#define CONFIG      0x00  /* 'Config' register address */
#define EN_AA       0x01  /* 'Enable Auto Acknowledgment' register address */
#define EN_RXADDR   0x02  /* 'Enabled RX addresses' register address */
#define SETUP_AW    0x03  /* 'Setup address width' register address */
#define SETUP_RETR  0x04  /* 'Setup Auto. Retrans' register address */
#define RF_CH       0x05  /* 'RF channel' register address */
#define RF_SETUP    0x06  /* 'RF setup' register address */
#define STATUS      0x07  /* 'Status' register address */
#define OBSERVE_TX  0x08  /* 'Observe TX' register address */
#define CD          0x09  /* 'Carrier Detect' register address */
#define RX_ADDR_P0  0x0A  /* 'RX address pipe0' register address */
#define RX_ADDR_P1  0x0B  /* 'RX address pipe1' register address */
#define RX_ADDR_P2  0x0C  /* 'RX address pipe2' register address */
#define RX_ADDR_P3  0x0D  /* 'RX address pipe3' register address */
#define RX_ADDR_P4  0x0E  /* 'RX address pipe4' register address */
#define RX_ADDR_P5  0x0F  /* 'RX address pipe5' register address */
#define TX_ADDR     0x10  /* 'TX address' register address */
#define RX_PW_P0    0x11  /* 'RX payload width, pipe0' register address */
#define RX_PW_P1    0x12  /* 'RX payload width, pipe1' register address */
#define RX_PW_P2    0x13  /* 'RX payload width, pipe2' register address */
#define RX_PW_P3    0x14  /* 'RX payload width, pipe3' register address */
#define RX_PW_P4    0x15  /* 'RX payload width, pipe4' register address */
#define RX_PW_P5    0x16  /* 'RX payload width, pipe5' register address */
#define FIFO_STATUS 0x17  /* 'FIFO Status Register' register address */


uint8_t SPI_RW(uint8_t byte);
uint8_t SPI_RW_Reg(uint8_t reg, uint8_t value);
uint8_t SPI_Read(uint8_t reg);
uint8_t SPI_Read_Buf(uint8_t reg, uint8_t* pBuf, uint8_t bytes);
uint8_t SPI_Write_Buf(uint8_t reg, uint8_t* pBuf, uint8_t bytes);
void nRF_Init(void);
void SetRX_Mode(void);
uint8_t nrf_read(uint8_t* rx_buf);
void nrf_send(uint8_t* tx_buf);
void delay_us(uint16_t x);
void delay_ms(uint16_t x);

#endif
