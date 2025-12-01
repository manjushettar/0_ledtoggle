#ifndef UART_H
#define UART_H

#include "stm32f446xx.h"
#define UART2EN                   (1U<<17)
#define CR1_TE                    (1U<<3)
#define CR1_UE                    (1U<<13)
#define CR1_RE                    (1U<<2)

#define SYS_FREQ                  16000000
#define APB1_CLK                  SYS_FREQ
#define UART_BAUDRATE             115200

#define SR_RXNE                   (1U<<5)
#define SR_TXE                    (1U<<7)
static void uart_set_baudrate(USART_TypeDef *USARTx,
                              uint32_t PeriphClk,
                              uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t PeriphClk,
                                uint32_t BaudRate);

char uart2_read();
void uart2_write(int ch);
void uart2_tx_init();
void uart2_rxtx_init();
#endif
