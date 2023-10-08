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

class HardwareHandler
{
private:
    /*uint16_t sensor_value;*/
    uint16_t pin;
    int minValue;
    int maxValue; 
    bool calibrated;
    unsigned long calibrationStartTime; 
    unsigned long lastSyncTime;
    unsigned long syncInterval;
public:
    HardwareHandler(uint16_t pin);
    void calibrate (); 
    void sync();
    int readValue();
    //int getMappedValue();
    bool isCalibrated();
};

#endif /* !HARDWAREHANDLER_H_ */
