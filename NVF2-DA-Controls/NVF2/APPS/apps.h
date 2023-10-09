/*
** EPITECH PROJECT, 2023
** NVF2-DA-Controls
** File description:
** apps
*/

#ifndef APPS_H_
#define APPS_H_

#include <Arduino.h>
#include <stdint.h>

#include "hardwareHandler.h"

struct analogSensor_t
{
    uint64_t sensorMax;
    uint64_t sensorMin;
};

class apps
{
private:
    bool isInited = 0;

    pin_size_t sensorPin;
    PinModeType sensorModeType;
    pin_size_t syncPin;
    bool syncPinStatus = 0;

    analogSensor_t sensorConfig;
    uint64_t sensorCurrVal;

public:
    apps(pin_size_t *, pin_size_t * = nullptr);
    bool begin(PinModeType = PinModeType::ANALOG, *analogSensor_t);
    void readSensorVal();
    void readSyncVal();

    void getRawSensorVal(uint64_t *);
    void getMappedSensorVal(uint8_t *);

    bool calibrate();
    bool calibrateIfRequested();
};

apps::apps(pin_size_t *syncPin, pin_size_t *sensorPin)
{
    this->sensorPin = *sensorPin;
    this->syncPin = *syncPin;

    pinMode(this->syncPin, INPUT_PULLDOWN);
    if (this->sensorPin != nullptr)
    {
        pinMode(this->sensorPin, INPUT);
    }
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
        this->sensorCurrVal < this->sensorConfig.sensorMin
        )
        {
            return 0;
        }

    *buf = map(this->sensorCurrVal, 
        this->sensorConfig.sensorMin, this->sensorConfig.sensorMax,
        0, 100);
    
    return 1;
}

void apps::readSensorVal()
{
    if (this->sensorModeType == PinModeType::ANALOG)
    {
        this->sensorCurrVal = analogRead(this.sensorPin);
    }
    else if (this->sensorModeType == PinModeType::ANALOG_I2C)
    {
        // use commsHandler to read from i2c
    }
    else if (this->sensorModeType == PinModeType::ANALOG_SPI)
    {
        // use commsHandler to read from spi
    }
}

void apps::readSyncVal()
{
    this->syncPinStatus = digitalRead(this->syncPin);
}

bool apps::calibrateIfRequested()
{
    this->readSyncVal();
    if (this->syncPinStatus)
    {
        this->calibrate();
        return 1;
    }
    return 0;
}

bool apps::calibrate()
{
    uint64_t minVal = (uint64_t)-1; // retrieve max value of uint64_t
    uint64_t maxVal = 0;            // use lowest value of uint64_t
    uint64_t val;
    bool stopCalibrate = false;

    do
    {
        this->pCommsHandler->CAN_RX();

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
        this->pCommsHandler->CAN_TX();
    } while (1);
}

bool apps::begin(PinModeType pinModeType, analogSensor_t sensorConfig)
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
    this->sensorConfig = new analogSensor_t(sensorConfig);

    return 1;
}

#endif /* !APPS_H_ */
