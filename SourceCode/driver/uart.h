/*
I2C 地址占用列表
-------------------------------------------

 Si4754：0xC2（可用地址四个：0xC0, 0xC2, 0xC4, 0xC6）
 ZL3560: 0x80
*/

#ifndef _UART_H
#define _UART_H

#include "../typedef.h"
#include "ring_buffer.h"

#ifdef HAVE_UART

/* GPIO for UART */
#define UART_GPIO_PORT          GPIOC
#define UART_TX_PIN             GPIO_Pin_5
#define UART_TX_PORT            GPIOC
#define UART_RX_PIN             GPIO_Pin_6
#define UART_RX_PORT            GPIOC


void Uart_Inerface_Init(void);

void uart_send(uint8_t* buff, uint8_t size);

PRING_BUFFER getUartTxBuffer();

uint8_t uart_received(uint8_t byte);

PRING_BUFFER getUartRxBuffer();


void uart_suspend();

void uart_wakeup();

#endif

#endif	//_I2C_H
