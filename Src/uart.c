#include "uart.h"
#include "NucleoFpga.h"
int __io_putchar(int ch)
{
  uart2_write(ch);
  return ch;
}

static void uart_set_baudrate(USART_TypeDef *USARTx,
                              uint32_t PeriphClk,
                              uint32_t BaudRate)
{
  USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk,
                        uint32_t BaudRate)
{
  // (Peripheral Clock + BaudRate / 2) / BaudRate
  uint16_t result = ((PeriphClk + (BaudRate / 2U)) / BaudRate);
  return result;
}

char uart2_read()
{
  while(!(USART2->SR & SR_RXNE)){}
  printf("[UART2_READ]: %c\n\r", USART2->DR);
  return USART2->DR;
}

void uart2_write(int ch)
{
  // Make sure transmit data register is empty
  while(!(USART2->SR & SR_TXE)){}
  // Write to transmit data register
  USART2->DR = (ch & 0xFF);
}

void uart2_tx_init(void)
{
  // Configure uart gpio pin
  // Enable clock access to gpioa
  RCC->AHB1ENR |= GPIOAEN;
  // Set PA2 mode to alternate function mode
  GPIOA->MODER &=~ (1U<<4);
  GPIOA->MODER |= (1U<<5);

  // Set PA2 alternate function type to UART_TX
  GPIOA->AFR[0] |= (1U<<8);
  GPIOA->AFR[0] |= (1U<<9);
  GPIOA->AFR[0] |= (1U<<10);
  GPIOA->AFR[0] &=~ (1U<<11);

  // Configure uart module
  // Enable clock access to uart2
  RCC->APB1ENR |= UART2EN;
  // Configure baudrate
  uart_set_baudrate(USART2, SYS_FREQ, UART_BAUDRATE);  
  // Configure the transfer direction
  USART2->CR1 = CR1_TE;

  // Enable UART module
  USART2->CR1 |= CR1_UE;
}

void uart2_rxtx_init()
{
  // Configure uart gpio pin
  // Enable clock access to gpioa
  RCC->AHB1ENR |= GPIOAEN;
  // Set PA2 mode to alternate function mode
  GPIOA->MODER &=~ (1U<<4);
  GPIOA->MODER |= (1U<<5);
  
  // Set PA2 alternate function type to UART_TX
  GPIOA->AFR[0] |= (1U<<8);
  GPIOA->AFR[0] |= (1U<<9);
  GPIOA->AFR[0] |= (1U<<10);
  GPIOA->AFR[0] &=~ (1U<<11);

  // Set up PA3 for RX
  GPIOA->MODER &=~ (1U<<6);
  GPIOA->MODER |= (1U<<7);

  GPIOA->AFR[0] |= (1U<<12);
  GPIOA->AFR[0] |= (1U<<13);
  GPIOA->AFR[0] |= (1U<<14);
  GPIOA->AFR[0] &=~ (1U<<15);

  // Configure uart module
  // Enable clock access to uart2
  RCC->APB1ENR |= UART2EN;
  // Configure baudrate
  uart_set_baudrate(USART2, SYS_FREQ, UART_BAUDRATE);  
  // Configure the transfer direction
  USART2->CR1 = (CR1_TE | CR1_RE);
  // Enable UART module
  USART2->CR1 |= CR1_UE;
}
