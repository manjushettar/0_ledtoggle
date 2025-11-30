/*
 * Nucleo Register spec
 */

#ifndef NUCLEO_FPGA_H
#define NUCLEO_FPGA_H

#include "stm32f446xx.h"
// Memory Mapping -> peripheral base to find location
// of Peripheral mapping in memory
#define PERIPHERAL_BASE           (0x40000000UL)

// We looked at the board block diagram to determine
// that GPIO Port A is connected to AHB1.
// We took the start of AHB1's offset and made a BASE
// out of it.
#define AHB1_PERIPHERAL_OFFSET    (0x00020000UL)
#define AHB1_PERIPHERAL_BASE      (PERIPHERAL_BASE + AHB1_PERIPHERAL_OFFSET)

// GPIOA memory mapping starts at offset 0
#define GPIOA_OFFSET              (0x0000UL)
#define GPIOA_BASE                (AHB1_PERIPHERAL_BASE + GPIOA_OFFSET)
// 0000 0000 0000 0000 0000 0000 0000 0000
// (SHIFT ONE TO POSITION 0)
// 0000 0000 0000 0000 0000 0000 0000 0001

#define GPIOAEN                   (1U<<0)
#define GPIOA                     ((GPIO_TypeDef*) GPIOA_BASE)

// we also need the RCC to provide the clock
#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1_PERIPHERAL_BASE + RCC_OFFSET)
#define RCC                       ((RCC_TypeDef*) RCC_BASE)

// Pin 5 at GPIO port A
#define PIN5                      (1U<<5)
#define LED_PIN                   PIN5

#define MAX_LED_LOOPS             10000000

#define PIN5_BSR_RESET            (1U<<21)
#define LED_PIN_RESET             PIN5_BSR_RESET

#define PIN13                     (1U<<13)
#define BTN_PIN                   PIN13

#define GPIOC_OFFSET              (0x0800UL)
#define GPIOC_BASE                (AHB1_PERIPHERAL_BASE + GPIOC_OFFSET)

#define GPIOCEN                   (1U<<2)
#define GPIOC                     ((GPIO_TypeDef*) GPIOC_BASE)

#endif
