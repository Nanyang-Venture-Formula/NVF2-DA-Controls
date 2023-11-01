/*
** EPITECH PROJECT, 2023
** NVF2-DA-Controls
** File description:
** apps
*/

#include "apps.h"

apps::apps(uint8_t syncPin, uint8_t sensorPin)
{
    this->sensorPin = sensorPin;
    this->syncPin = syncPin;

    pinMode(this->syncPin, INPUT);
    if (this->sensorPin != 0)
    {
        pinMode(this->sensorPin, INPUT);
    }
}

bool apps::begin(analogSensor_t sensorConfig, PinModeType pinModeType)
{
    this->sensorModeType = pinModeType;

    if (pinModeType == PinModeType::ANALOG)
    {
        // begin analog
    }
    else if (pinModeType == PinModeType::ANALOG_I2C)
    {
        // begin i2c
    }
    else if (pinModeType == PinModeType::ANALOG_SPI)
    {
        // begin spi
    }

    // cpy sensorConfig
    this->sensorConfig = analogSensor_t(sensorConfig);

    return 1;
}

/**
 *readSensorVal() explanation
 * Return sensorCurrVal (raw value)
 * first read of APPS value 
*/

uint8_t apps::readSensorVal()
{
    uint8_t SensorValue = 0;
    if (this->sensorModeType == PinModeType::ANALOG)
    {
        SensorValue = analogRead(this->sensorPin);
    }
    else if (this->sensorModeType == PinModeType::ANALOG_I2C)
    {
        // use commsHandler to read from i2c
    }
    else if (this->sensorModeType == PinModeType::ANALOG_SPI)
    {
        // use commsHandler to read from spi
    }
    this->sensorCurrVal = SensorValue;
    return SensorValue; 
}

void apps::getRawSensorVal(uint64_t *buf)
{
    *buf = this->sensorCurrVal;
}

bool apps::getMappedSensorVal(uint8_t *buf)
{
    // catch to make sure the values are not out of bounds
    // if OOB, perhaps short circuit/ error in reading
    if (
        this->sensorCurrVal > this->sensorConfig.sensorMax ||
        this->sensorCurrVal < this->sensorConfig.sensorMin)
    {
        return 0;
    }

    *buf = map(this->sensorCurrVal,
               this->sensorConfig.sensorMin, this->sensorConfig.sensorMax,
               0, 0xFF);

    return 1;
}

void apps::readSyncVal()
{
    this->syncPinStatus = digitalRead(this->syncPin);
}


bool apps::calibrateIfRequested(CommsHandler *pCommsHandler)
{
    this->readSyncVal();
    if (this->syncPinStatus)
    {
        this->calibrate(pCommsHandler);
        return 1;
    }
    return 0;
}

bool apps::calibrate(CommsHandler *pCommsHandler)
{
    uint64_t minVal = (uint64_t)-1; // retrieve max value of uint64_t
    uint64_t maxVal = 0;            // use lowest value of uint64_t
    uint64_t val;
    bool stopCalibrate = false;

    do
    {
        //pCommsHandler->CAN_RX();

        this->readSyncVal();
        if (this->syncPinStatus == 0)
        {
            break;
        }

        // read value
        this->readSensorVal();

        // populate min and max values
        if (this->sensorCurrVal < minVal)
        {
            minVal = this->sensorCurrVal;
        }
        if (this->sensorCurrVal > maxVal)
        {
            maxVal = this->sensorCurrVal;
        }

        // report max, min vals.
        //pCommsHandler->CAN_TX(can_frame*);
    } while (1);
    return 0;
}
