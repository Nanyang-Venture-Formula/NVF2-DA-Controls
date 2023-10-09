#include "hardwareHandler.h"

HardwareHandler::HardwareHandler(uint16_t pin)
{
    this->pin = pin; 
    this->calibrated = false; 
    this->minValue = 0;
    this->maxValue = 1023;
    this->calibrationStartTime = 0;
    pinMode(pin, INPUT); 
}

HardwareHandler::HardwareHandler(uint16_t pin, PinMode pin_mode, PinModeType pinModeType)
{
    this->pin = pin;
    this->pin_mode = pin_mode;
    this->pinModeType = pinModeType;
    this->minValue = 0;
    this->maxValue = 0;
    pinMode(pin, pin_mode);
}

bool HardwareHandler::begin()
{
    
}

uint32_t HardwareHandler::getMappedValue()
{
}

void HardwareHandler::calibrate()
{
    int sensorValue = analogRead(pin);
    if (!calibrated || sensorValue < minValue ||  sensorValue > maxValue){
        //start or reset the calibration timer 
        if(!calibrated){
            calibrationStartTime = millis();
        }
        
        //update the maximum and minimum value if requried
        if (sensorValue < minValue){
            minValue = sensorValue;
        } 

        if (sensorValue > maxValue){
            maxValue = sensorValue;
        } 

        //check if the calibration is completed 
        if(millis() - calibrationStartTime > calibration_period){
            calibrated = true;
            Serial.println("Caibration Completed!");
        }   
    }
}

void HardwareHandler::sync()
{
    unsigned long currentTime = millis();
    if(currentTime - lastSyncTime >= syncInterval){
        lastSyncTime = currentTime;
    }
}

int HardwareHandler::readValue()
{
    return analogRead(pin);
}

// int HardwareHandler::getMappedValue()
// {
//     int sensorValue = readValue();
//     sensorValue = constrain(sensorValue, minValue, maxValue);
//     /**
//      * should we force the sensor value to be in the range 
//      * or show alert signal when out of the range
//     */
//     int mappedValue = map(sensorValue, minValue, maxValue, 0, 100);
//     return mappedValue;
// }

bool HardwareHandler::isCalibrated()
{
    return calibrated;
}