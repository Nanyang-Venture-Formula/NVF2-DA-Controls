/*
** EPITECH PROJECT, 2023
** NVF2-DA-Controls
** File description:
** hardwareHandler
*/

#ifndef HARDWAREHANDLER_H_
#define HARDWAREHANDLER_H_

#include "stdint.h"

class HardwareHandler
{
private:
    uint16_t sensor_value;
    uint16_t pin;

public:
    HardwareHandler(uint16_t);
};

HardwareHandler::HardwareHandler(uint16_t Pin)
{
}


#endif /* !HARDWAREHANDLER_H_ */
