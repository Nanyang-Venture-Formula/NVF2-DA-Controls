/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** boardDef
*/

#ifndef BOARDDEF_H_
#define BOARDDEF_H_

#include <Arduino.h>
#include "stdint.h"
namespace BoardDef
{
    const uint8_t PIN_CANSPI_CSN1 = 10;
    const uint8_t PIN_CANSPI_CSN2 = 9;

    const uint8_t PIN_CANSPI_MOSI = 0;
    const uint8_t PIN_CANSPI_MISO = 0;
    const uint8_t PIN_CANSPI_MCLK = 0;
    const uint8_t PIN_CANSPI_INT = 0;

    const uint8_t PIN_AIR_TRIGGER_OUT = 0;

    const uint8_t PIN_SYNC_PIN = 0;

    const uint8_t PIN_ADC_1_0 = 0;
}

#endif /* !BOARDDEF_H_ */
