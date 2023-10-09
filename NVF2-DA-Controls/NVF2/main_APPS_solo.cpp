/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_APPS_solo
*/

#include <Arduino.h>
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"
#include "NVF2/boardDef.h"
#include "NVF2/hardwareHandler.h"

#define APPS 1

CommsHandler commsHandler;
systemComms_t TIComms;

#ifdef APPS
    #if APPS == 1
        const uint32_t this_can_id = CommsDef::APPS1_CAN_ID;
    #elif APPS == 2
        const uint32_t this_can_id = CommsDef::APPS2_CAN_ID;
    #endif
#endif

// limits of apps analog value
uint32_t limit_high;
uint32_t limit_high;
HardwareHandler apps_hwh(BoardDef::PIN_ADC_1_0);

void setup()
{
    Serial.begin(115200);
    
    commsHandler = CommsHandler();
    commsHandler.begin();
    // todo make this dynamic
    commsHandler.CAN_begin(CommsDef::APPS1_CAN_ID, BoardDef::PIN_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    TIComms = systemComms_t();
    TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;

    apps_hwh;
    // check if calibration/sync mode is requested
    pinMode(BoardDef::PIN_SYNC_PIN, INPUT_PULLUP);
    if (digitalRead(BoardDef::PIN_SYNC_PIN))
    {
        // run calibrate mode
        apps_hwh.calibrate();

        // wait for reset signal
        while (1);
    }
}

void loop()
{
    // recieve CAN buffer
    commsHandler.CAN_RX();

    apps_hwh.readValue();

    commsHandler.CAN_TX();
}

