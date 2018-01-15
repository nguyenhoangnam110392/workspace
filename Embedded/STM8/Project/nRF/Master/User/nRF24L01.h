#ifndef __NRF24L01_H_
#define __NRF24L01_H_

#include "main.h"

/********** API *************/
void nRF24L01_Pin_Config(void);
void nRF24L01_Set_TxMode(void);
void nRF24L01_SendData(uint8_t *data);
void nRF24L01_SendData(uint8_t *data);
uint8_t nRRF24L01_CheckACK(void);
void nRF24L01_Set_RxMode(void);
uint8_t nRF24L01_RevData(uint8_t *RevData);

/* Define SPI pins */
#define CE_PORT    GPIOC
#define CE_PIN     GPIO_PIN_3
#define CSN_PORT   GPIOC
#define CSN_PIN    GPIO_PIN_4
#define SCK_PORT   GPIOC
#define SCK_PIN    GPIO_PIN_5

#define TX_ADDR_WITDH    5   /* Send address width is set to 5 bytes */
#define RX_ADDR_WITDH    5   /* Receive address width set to 5 bytes */
#define TX_DATA_WITDH    32  /* Transmission data width 4 bytes */
#define RX_DATA_WITDH    32  /* Receive data width 4 bytes */


/*
  * Command register
  */
#define R_REGISTER       0x00   /* Read Configuration Register */
#define W_REGISTER       0x20   /* Write Configuration Register */
#define R_RX_PAYLOAD     0x61   /* Read RX Valid Data */
#define W_TX_PAYLOAD     0xa0   /* Write TX Valid Data */
#define FLUSH_TX         0xe1   /* Clear TXFIFO register */
#define FLUSH_RX         0xe2   /* Clear RXFIFO register */
#define REUSE_TX_PL      0xe3   /* Reuse the last packet of valid data */
#define NOP              0xff   /* No operation */

/*
 * Register address
 */
#define CONFIG           0x00 /* Configuration Register */
#define EN_AA            0x01 /* Enable auto-answer */
#define EN_RXADDR        0x02 /* Receive Channel Enabled 0-5 channels */
#define SETUP_AW         0x03 /* Set the data channel address width 3-5 */
#define SETUP_RETR       0x04 /* Create automatic retransmission */
#define RF_CH            0x05 /* RF channel settings */
#define RF_SETUP         0x06 /* RF Register */
#define STATUS           0x07 /* Status Register */
#define OBSERVE_TX       0x08 /* send detection register */
#define CD               0x09 /* Carrier */
#define RX_ADDR_P0       0x0a /* Data channel 0 receive address */
#define RX_ADDR_P1       0x0b /* Data channel 1 receive address */
#define RX_ADDR_P2       0x0c /* Data channel 2 receive address */
#define RX_ADDR_P3       0x0d /* Data channel 3 receive address */
#define RX_ADDR_P4       0x0e /* Data channel 4 receive address */
#define RX_ADDR_P5       0x0f /* Data channel 5 receive address */
#define TX_ADDR          0x10 /* Send Address */
#define RX_PW_P0         0x11 /* P0 Channel Data Width Setting */
#define RX_PW_P1         0x12 /* P1 channel data width setting */
#define RX_PW_P2         0x13 /* P2 channel data width setting */
#define RX_PW_P3         0x14 /* P3 channel data width setting */
#define RX_PW_P4         0x15 /* P4 channel data width setting */
#define RX_PW_P5         0x16 /* P5 Channel data width setting */
#define FIFO_STATUS      0x17 /* FIFO status register */

#endif
