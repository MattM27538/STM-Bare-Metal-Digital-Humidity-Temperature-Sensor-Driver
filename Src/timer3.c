#include "timer3.h"
#include "stm32f4xx.h"
#include "stdint.h"

void timer3Init(const uint32_t prescalerValue){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3->PSC = prescalerValue-1;

	const uint16_t counterStartValue = 0;
	TIM3->CNT = counterStartValue;

	TIM3->CR1 |= TIM_CR1_CEN;
}

void resetTimer3Counter(){
	TIM3->CR1 &= (~TIM_CR1_CEN);

	const uint16_t counterStartValue = 0;
	TIM3->CNT = counterStartValue;

	TIM3->CR1 |= TIM_CR1_CEN;
}

uint32_t getTimer3CounterValue(){
	uint32_t timer3CounterValue;
	timer3CounterValue = TIM3->CNT;
	return timer3CounterValue;
}
