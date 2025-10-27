#include "i2c.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

void i2cInit(){
    enableI2CClock();

    setPB9andPB9ToAltFunctionI2C();

    setPB8AndPB9AsOpenDrain();

    softwareResetI2C();

    const uint32_t i2cClockFrequencyMHz = 50;
    setI2CClockFrequency(i2cClockFrequencyMHz);

    const uint32_t fastMode = 1U << 15;
    setI2CMode(fastMode);

    const uint32_t dutyCycle16Low9High = 1U << 14;
    setI2CModeDutyCycle(dutyCycle16Low9High);

    const uint32_t clockSpeed = 1U << 1;
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

//TODO: account for return type / abstract functions
void i2cReadByte(char controllerAddress, char targetAddress, char *receivedData){
    volatile int statusRegisterValue;

    while(i2cBusIsBusy()){
    }
    
    startI2CBus();   

    while(!(startCommandAcknowledged())){
    }

    setTargetAddressAndWritebit();

    while(!(targetAddressAcknowledged())){
    }

    clearAddressFlag();

    while(!(dataRegisterIsEmpty())){
    }

    setControllerAddress();

    while(!(dataRegisterIsEmpty())){
    }

    startI2CBus();

    while(!(startCommandAcknowledged())){
    }

    setTargetAddressAndReadBit();
    
    while(!(targetAddressAcknowledged())){
    }

    disableAcknowledgeBit();

    clearAddressFlag();

    stopI2CBus();

    while(!(receiveBufferIsEmpty())){
    }

    readDataFromDataRegister(receivedData);
}

bool i2cBusIsBusy(){
    return I2C1->SR2 & I2C_SR2_BUSY;
}

void startI2CBus(){
    I2C1->CR1 |= I2C_CR1_START;
}

//ToDo: Consider combining with setTargetAddressAndReadBit
void setTargetAddressAndWritebit(){
    I2C1->DR = targetAddress << 1;
}

bool startCommandAcknowledged(){
    return I2C1->SR1 & I2C_SR1_SB;
} 

bool targetAddressAcknowledged(){
    return I2C1->SR1 & I2C_SR1_ADDR;
}

void clearAddressFlag(){
    statusRegisterValue = I2C1->SR2;
}

bool dataRegisterIsEmpty(){
    return I2C1->SR1 & I2C_SR1_TXE;
}

void setControllerAddress(){
    I2C1->DR = controllerAddress;
}

void setTargetAddressAndReadBit(){
    I2C1->DR = targetAddress << 1 | 1;
}

void disableAcknowledgeBit(){
    I2C1->CR1 &= (~I2C_CR1_ACK);
}

void stopI2CBus(){
    I2C1->CR1 |= I2C_CR1_STOP;
}

bool receiveBufferIsEmpty(){
    I2C1->SR1 & I2C_SR1_RXNE;
}

void readDataFromDataRegister(char *receivedData){
    *receivedData = I2C1->DR;
    ++receivedData;
}
