#include "timer3.h"
#include "stm32f4xx.h"
#include "delay.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct DHT11TemperatureAndHumidity{
	uint8_t temperature;
	uint8_t humidity;
} DHT11SensorData;

int8_t readDHT11() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	setPA8ToOutput();

	setPA8OutputToLow();
	
	delay(18);
	
	setPA8OutputToHigh();
	
	resetTimer3();

	//TODO: Move to func.
	for(int i = 0; i < 1000; ++i);

	setPA8ToInput();

	unsigned int loopCnt = 1000000;

	const int8_t errorCode = -2;

	while(!(GPIOA8InputIsHigh())){
		if (loopCnt-- == 0) return errorCode;
	}

	loopCnt = 10000;

	while((GPIOA8InputIsHigh())){
		if (loopCnt-- == 0) return errorCode;
	}

	for (int i = 0; i < 40; ++i){
    	loopCnt = 100000;
		while(!(GPIOA8InputIsHigh())){
			if (loopCnt-- == 0) return errorCode;
		}

		uint32_t initialTimer3CounterValue = getTimer3CounterValue();

		loopCnt = 1000000;
		while((GPIOA8InputIsHigh())){
			if (loopCnt-- == 0){
				return -2;
			}
		}
		
		//TODO: create struct
		uint8_t dht11InformationBytes[5] = {0};
		uint8_t shiftCount = 7;
		uint8_t byteIndex = 0;

		//TODO: change var name
		const uint32_t maxTimer3Value = 40;

		if ((getTimer3CounterValue() - initialTimer3CounterValue) > maxTimer3Value){
			dht11InformationBytes[byteIndex] |= (1 << shiftCount)
		};

		if (shiftCount == 0){
			shiftCount = 7;
			++byteIndex;
		}
		else {
			--shiftCount;
		};
  	}

	DHT11SensorData.temperature = bits[2];
	DHT11SensorData.humidity = bits[0];
	uint8_t sumHumidityAndTemperature = bits[0] + bits[2];

	uint8_t checkSum= bits[4];

	const int8_t checkSumError = -1;

	if (sumHumidityAndTemperature != checkSum){
		return checkSumError;
	}

  	return 0;
}

void setPA8ToOutput(){
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
}

void setPA8OutputToLow(){
	GPIOA->ODR &= ~(GPIO_ODR_OD8);
}

void setPA8OutputToHigh(){
	GPIOA->ODR |= GPIO_ODR_OD8;
}

void setPA8ToInput(){
	GPIOA->MODER &= ~(GPIO_MODER_MODE8_0);
}

bool GPIOA8InputIsHigh(){
	return GPIOA->IDR & GPIO_IDR_ID8;
}

uint8_t getTemperature(){
	return DHT11SensorData.temperature;
}

uint8_t getHumidity(){
	return DHT11SensorData.humidity;
}