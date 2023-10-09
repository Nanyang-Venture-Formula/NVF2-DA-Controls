/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** hardwareHandler
*/

#ifndef HARDWAREHANDLER_H_
#define HARDWAREHANDLER_H_

#include <Arduino.h>
#include "stdint.h"

enum PinModeType
{
    ANALOG,
    DIGITAL
}

class HardwareHandler
{
private:
    /*uint16_t sensor_value;*/
    uint16_t pin;
    PinMode pin_mode;
    PinModeType pinModeType;

    int minValue;
    int maxValue; 
    bool calibrated;
    unsigned long calibrationStartTime; 
    unsigned long lastSyncTime;
    unsigned long syncInterval;
public:
    HardwareHandler(uint16_t, PinMode, PinModeType);
    bool begin();

    HardwareHandler(uint16_t pin);
    void calibrate (); 
    void sync();
    int readValue();
    uint32_t getMappedValue();
    bool isCalibrated();
};

#endif /* !HARDWAREHANDLER_H_ */
