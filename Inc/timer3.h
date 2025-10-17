#include <stdint.h>

#ifndef timer3_h
#define timer3_h

void timer3Init(uint32_t prescalerValue);
void resetTimer3Counter();
uint32_t getTimer3CounterValue();

#endif
