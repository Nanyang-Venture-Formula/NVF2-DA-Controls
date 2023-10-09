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

#include "NVF2/commsHandler.h"

enum PinModeType
{
    DIGITAL,
    ANALOG,
    ANALOG_I2C,
    ANALOG_SPI
};

struct analogSensor_t
{
    uint64_t sensorMax;
    uint64_t sensorMin;
};

class apps
{
private:
    bool isInited = 0;

    pin_size_t sensorPin = 0;
    PinModeType sensorModeType;
    pin_size_t syncPin = 0;
    bool syncPinStatus = 0;

    analogSensor_t sensorConfig;
    uint64_t sensorCurrVal;

public:
    apps(pin_size_t, pin_size_t = 0);
    bool begin(analogSensor_t, PinModeType = PinModeType::ANALOG);
    void readSensorVal();
    void readSyncVal();

    void getRawSensorVal(uint64_t *);
    bool getMappedSensorVal(uint8_t *);

    bool calibrate(CommsHandler *);
    bool calibrateIfRequested(CommsHandler *);
};


#endif /* !APPS_H_ */
