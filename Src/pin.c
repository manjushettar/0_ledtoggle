#include "NucleoFpga.h"
#include "stm32f446xx.h"

void enable_ahb1_clock_access(int gpioPort)
{
  RCC->AHB1ENR |= gpioPort;
}


