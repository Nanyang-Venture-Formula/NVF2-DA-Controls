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

#include "NVF2/APPS/apps.h"

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

// HardwareHandler apps_hwh(BoardDef::PIN_ADC_1_0);
apps appsHandler(BoardDef::PIN_SYNC_PIN, BoardDef::PIN_ADC_1_0);

void setup()
{    
    commsHandler = CommsHandler();
    commsHandler.begin();
    // todo make this dynamic
    commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    TIComms = systemComms_t();
    TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;

    analogSensor_t appsSensorCfg;
    // get values from eeprom
    appsSensorCfg.sensorMin = 0;
    appsSensorCfg.sensorMax = 0;
    appsHandler.begin(PinModeType::ANALOG, &appsSensorCfg);

    if(appsHandler.calibrate())
    {
        // meaning sensor did calibrate, restart
        // restart node
        // inform system node restarting.
    }

}

void loop()
{
    // recieve CAN buffer
    commsHandler.CAN_RX();

    appsHandler.readSensorVal();


    commsHandler.CAN_TX();
}

