#include "i2c.h"
#include "stm32f4xx.h"
#include <stdint.h>

void i2c_init(){
    enableI2CClock();

    setPB9andPB9ToAltFunctionI2C();

    setPB8AndPB9AsOpenDrain();

    softwareResetI2C();

    const uint32_t i2cClockFrequencyMHz = 50;
    setI2CClockFrequency(i2cClockFrequencyMHz);

    const uint32_t fastMode = 1U<<15;
    setI2CMode(fastMode);

    const uint32_t dutyCycle16Low9High = 1U<<14;
    setI2CModeDutyCycle(dutyCycle16Low9High);

    const uint32_t clockSpeed = 1U<<1;
    setI2CClockSpeed(clockSpeed);

    const uint32_t maximumRiseTime = 20;
    setI2CSignalMaximumRiseTime(maximumRiseTime);

    void enableI2C();
}

void enableI2CClock(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
}

void setPB9andPB9ToAltFunction(){
    GPIOB->MODER |= 0xA0000;
    GPIOB->AFR[1] |= 0x44;
}

void setPB8AndPB9AsOpenDrain(){
    GPIOB->OTYPER |= GPIO_OTYPER_OT8|GPIO_OTYPER_OT9;
}

void softwareResetI2C(){
    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 &= (~I2C_CR1_SWRST);	
}

void setI2CClockFrequency(const uint32_t i2cClockFrequencyMHz){
    I2C1->CR2 |= i2cClockFrequencyMHz;
}

void setI2CMode(const uint32_t fastMode){
    I2C1->CCR |= fastMode;
}

void setI2CModeDutyCycle(const uint32_t dutyCycle16Low9High){
    I2C1->CCR |= dutyCycle16Low9High;
}

void setI2CClockSpeed(const uint32_t clockSpeed){
    I2C1->CCR |= clockSpeed;
}

void setI2CSignalMaximumRiseTime(const uint32_t maximumRiseTime){
    I2C1->TRISE = maximumRiseTime;
}

void enableI2C(){
    I2C1->CR1 |= I2C_CR1_PE;
}