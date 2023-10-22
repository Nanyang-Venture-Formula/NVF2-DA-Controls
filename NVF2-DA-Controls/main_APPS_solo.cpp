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

#include "NVF2/APPS/apps.h"

#define APPS        1
#define DELAY_MS    250 

CommsHandler commsHandler;
systemComms_t TIComms;

#ifdef APPS
    #if APPS == 1
        const uint32_t this_can_id = CommsDef::APPS1_CAN_ID;
    #elif APPS == 2
        const uint32_t this_can_id = CommsDef::APPS2_CAN_ID;
    #endif
#endif

apps appsHandler(BoardDef::PIN_SYNC_PIN, BoardDef::PIN_ADC_1_0, this_can_id);
can_frame tx_buf;

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
    appsHandler.begin(appsSensorCfg, PinModeType::ANALOG);

    if(appsHandler.calibrateIfRequested(&commsHandler))
    {
        // meaning sensor did calibrate, restart
        // restart node
        // inform system node restarting.
    }
    commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);
}

void loop()
{
    commsHandler.CAN_RX(TIComms, int32_t recievedData); //recieve CAN Buffer from Comshandler
    
    appsHandler.readSensorVal(); //read in APPS 
    uint16_t mappedValue;

    //Note: getMappedSensorVal return 1 when sensor value in bound 
    if(appsHandler.getMappedSensorVal(&mappedValue)){
        tx_buf.data[0] = (uint8_t) mappedValue;
    }
    else{
        mappedValue = -1; 
        //define an impossible mapped value to trigger error message to throttleinterlock 
        tx_buf.data[0] = (uint8_t) mappedValue; 
    }
    delay(DELAY_MS);
}

