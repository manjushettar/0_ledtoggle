/*
 * Nucleo Register spec
 */

#ifndef NUCLEO_FPGA_H
#define NUCLEO_FPGA_H

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

// we also need the RCC to provide the clock
#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1_PERIPHERAL_BASE + RCC_OFFSET)

#define RCC_AHB1ENR_OFFSET        (0x30UL)
#define RCC_AHB1ENR               (* (volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

// 0000 0000 0000 0000 0000 0000 0000 0000
// (SHIFT ONE TO POSITION 0)
// 0000 0000 0000 0000 0000 0000 0000 0001

#define GPIOAEN                   (1U<<0) 

// Mode register 
// MODE_RX = configuring MODE of register (R) X
// We are dealing with PA5 - Port A, pin 5
#define MODER_OFFSET              (0x0UL)
#define GPIOA_MODER               (* (volatile unsigned int *) (GPIOA_BASE + MODER_OFFSET))

/*
MODERy[1:0]: Port x configuration bits (y = 0..15)

00: Input (reset state)
01: General purpose output mode
10: Alternate function mode
11: Analog mode
*/

// GPIO A output data register 
#define GPIOA_ODR_OFFSET          (0x14UL)
#define GPIOA_ODR                 (* (volatile unsigned int *)(GPIOA_BASE + GPIOA_ODR_OFFSET))

// Pin 5 at GPIO port A
#define PIN5                      (1U<<5)
#define LED_PIN                   PIN5

#define MAX_LED_LOOPS             10000000

#endif
