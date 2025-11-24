/*
 * Nucleo Register spec
 */

#ifndef NUCLEO_FPGA_H
#define NUCLEO_FPGA_H

// Memory Mapping -> peripheral base to find location
// of Peripheral mapping in memory
#define PERIPHERAL_BASE           (0x40000000UL)

#define __IO volatile

typedef struct{
  __IO uint32_t MODER;  // GPIO port mode register offset: 0x00
  __IO uint32_t OTYPER; // GPIO port output type register offset: 0x04
  __IO uint32_t OSPEEDR;// GPIO port output speed register offset: 0x08
  __IO uint32_t PUPDR;  // GPIO port pull-up/pull down register offset: 0x0C
  __IO uint32_t IDR;    // GPIO port input data register offset: 0x10
  __IO uint32_t ODR;    // GPIO port output data register offset: 0x14
  __IO uint32_t BSRR;   // GPIO port bit set/reset register offset: 0x18
  __IO uint32_t LCKR;   // GPIO port configuration lock register offset: 0x1C
  __IO uint32_t AFR[2]; // GPIO alternate function registers offset: 0x20 - 0x2 GPIO port input data register offset: 0x10
}GPIO_TypeDef;

typedef struct{
  __IO uint32_t dummy[12];
  __IO uint32_t AHB1ENR;  // RCC AHB1 enable register offset: 0x30
}RCC_TypeDef;


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


#endif
