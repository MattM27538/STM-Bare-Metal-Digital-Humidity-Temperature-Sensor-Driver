#include <stdint.h>

#ifndef DELAY_H_
#define DELAY_H_

void systick_init_ms(uint32_t freq);

void setSysTickTimerFrequencyToOneSecond(const uint32_t clockFrequencyInMilliseconds);

void resetSysTickCounter();

void enableSysTickInterrupt();

void setSysTickClockSourceToInternal();

void beginSysTickTimerCountDown();

#endif
