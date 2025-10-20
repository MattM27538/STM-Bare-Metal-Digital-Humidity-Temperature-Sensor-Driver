#include "stdint.h"
#include "micros.h"

#ifndef dht_h
#define dht_h

int8_t readDHT11();
uint8_t getTemperature();
uint8_t getHumidity();

#endif