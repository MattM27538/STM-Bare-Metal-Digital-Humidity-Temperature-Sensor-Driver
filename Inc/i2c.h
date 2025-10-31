#include <stdint.h>
#include <stdbool.h>

#ifndef I2C_H
#define I2C_H
    void i2cInit();
    void enableI2CClock();
    void setPB9andPB9ToAltFunctionI2C();
    void setPB8AndPB9AsOpenDrain();
    void softwareResetI2C();
    void setI2CClockFrequency(const uint32_t i2cClockFrequencyMHz);
    void setI2CMode(const uint32_t fastMode);
    void setI2CModeDutyCycle(const uint32_t dutyCycle16Low9High);
    void setI2CClockSpeed(const uint32_t clockSpeed);
    void setI2CSignalMaximumRiseTime(const uint32_t maximumRiseTime);
    void enableI2C();

    void i2cReadByte(char controllerAddress, char targetAddress, char *i2cData);
    bool i2cBusIsBusy();
    void startI2CBus();
    bool startCommandAcknowledged();
    void setI2CTargetAddressAndWritebit(char targetAddress);
    bool targetAddressAcknowledged();
    void clearAddressFlag();
    bool dataRegisterIsEmpty();
    void setI2CControllerAddress(const char controllerAddress);
    void setI2CTargetAddressAndReadBit(char targetAddress);
    void disableAcknowledgeBit();
    void stopI2CBus();
    bool receiveBufferIsEmpty();
    void readDataFromDataRegister(char *receivedData);

    void i2cWriteByte(char controllerAddress, char targetAddress, char data);
    void insertDataIntoDataRegister(const char data);
    bool dataTransferCompleted();

    void i2cWriteMultiBytes(char controllerAddress, char targetAddress, const char *buffer, const uint8_t bufferLength);
    void writeBytes(const char *buffer, const uint8_t bufferLength);
#endif