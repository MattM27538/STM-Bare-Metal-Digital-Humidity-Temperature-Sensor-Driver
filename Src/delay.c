#include <stdint.h>
#include "delay.h"
#include "stm32f4xx.h"

volatile uint64_t ms, rms;

void systick_init_ms(const uint32_t clockFrequencyInMilliseconds){
	__disable_irq();

	setSysTickTimerFrequencyToOneSecond(clockFrequencyInMilliseconds);

	resetSysTickCounter();

	enableSysTickInterrupt();

	setSysTickClockSourceToInternal();

	beginSysTickTimerCountDown();

	__enable_irq();
}

void setSysTickTimerFrequencyToOneSecond(const uint32_t clockFrequencyInMilliseconds){
	const uint32_t millisecondsInOneSecond = 1000;
	const uint32_t oneToAccountForCountdownIncludingZero = 1;
	SysTick->LOAD = (clockFrequencyInMilliseconds/millisecondsInOneSecond) - oneToAccountForCountdownIncludingZero;
}

void resetSysTickCounter(){
	SysTick->VAL = 0;
}

void enableSysTickInterrupt(){
	const uint32_t enableSysTickInterrupt = (1U<<1);
	SysTick->CTRL |= enableSysTickInterrupt;
}

void setSysTickClockSourceToInternal(){
	const uint32_t setClockSourceToInternal = (1U<<2);
	SysTick->CTRL |= setClockSourceToInternal;
}

void beginSysTickTimerCountDown(){
	const uint32_t enableSysTickTimer = (1U<<0);
	SysTick->CTRL |= enableSysTickTimer;
}
