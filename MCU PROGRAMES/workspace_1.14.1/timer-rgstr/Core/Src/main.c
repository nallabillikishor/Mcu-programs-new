#include "stm32f4xx.h"
int main(void)
{

RCC->AHB1ENR |= 1;
GPIOA->MODER &=~0x00000C00;

GPIOA->MODER |= 0x00000400;
RCC->APB1ENR |= 1;

TIM2->PSC = 1600 -1;
TIM2->ARR = 10000 -1;

TIM2->CNT = 0;
TIM2->CR1 = 0x11;
 while (1)
{
while (!(TIM2->SR & 1)) {}

TIM2->SR &= ~1;

GPIOA->ODR ^= 0x00000020;

}
}

