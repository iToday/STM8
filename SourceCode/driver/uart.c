/***********************************************************
Project  : T20
Compiler : T20
Version  : V1.0
Created  : 2010-01-06
Author   : Jason
Description
         Main function-
Modified
		 -
************************************************************/
#include "../typedef.h"

#include "uart.h"

#ifdef HAVE_UART

static RING_BUFFER uart_tx;
static RING_BUFFER uart_rx;


/* UART接口初始化 */
void Uart_Inerface_Init(void)
{

  init_ring_buffer(&uart_tx);
  init_ring_buffer(&uart_rx);
  
  GPIO_Init(UART_TX_PORT,UART_TX_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(UART_TX_PORT,UART_RX_PIN, GPIO_Mode_In_PU_No_IT);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
  USART_DeInit(USART1);
  USART_Init(USART1, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1,
             USART_Parity_No, USART_Mode_Tx | USART_Mode_Rx);

  USART_ITConfig(USART1,(USART_IT_RXNE|USART_IT_TC),ENABLE);
  
  USART_Cmd(USART1, ENABLE);
}

PRING_BUFFER getUartTxBuffer(){
   return &uart_tx;
}

PRING_BUFFER getUartRxBuffer(){
   return &uart_rx;
}

void uart_send(uint8_t* buff, uint8_t size){

    while(size --)
        uart_tx.push((void*)&uart_tx, *buff ++);

    USART1->CR2 |= 0x80;
}

uint8_t uart_received(uint8_t byte){

    uart_rx.push((void*)&uart_rx, byte);

    return 0;
}

void uart_suspend(){
    USART_Cmd(USART1, DISABLE);
    USART_DeInit(USART1);
    GPIO_Init(UART_RX_PORT,UART_RX_PIN, GPIO_Mode_Out_PP_Low_Slow);
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);
}

void uart_wakeup(){
    GPIO_Init(UART_RX_PORT,UART_RX_PIN, GPIO_Mode_In_PU_No_IT);
    Uart_Inerface_Init();
}
#endif
