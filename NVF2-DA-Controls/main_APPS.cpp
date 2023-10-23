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

#include "NVF2-CanFD/CanFD/NVF_Can.h"

#include "NVF2/APPS/apps.h"


#define APPS        1
#define DELAY_MS    1

#ifdef APPS
    #if APPS == 1
        const uint32_t this_can_id = CommsDef::APPS1_CAN_ID;
    #elif APPS == 2
        const uint32_t this_can_id = CommsDef::APPS2_CAN_ID;
    #endif
#endif

can_frame txBuf;

apps appsHandler(BoardDef::PIN_SYNC_PIN, BoardDef::PIN_ADC_1_0);

void setup()
{    
    commsHandler = CommsHandler();
    commsHandler.begin();
    // todo make this dynamic
    // commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);

    // nvfcan setup

    // define buffers for comms that i want to interact with
    // TIComms = systemComms_t();
    // TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;

    // APPSComms = systemComms_t();
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
    // commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);
    nvfcan.start;

}

void loop()
{
    // int32_t receivedData = 0;

    appsHandler.readSensorVal();
    if(appsHandler.getMappedSensorVal(&mappedValue)){
        txBuf.data[0] = mappedValue;
    }

    // might possible problems because of loss of data bits (msb/lsb??)
    // adc res -> 1023, uint8_t max = 255;
    // adc res > max data in a byte; sol: split data into 2 bytes
    // data[0] = val && 0xFF;
    // data[1] = val << 8;
    // check this

    nvfcan.tx(&txBuf);



    // if (commsHandler.CAN_RX(&TIComms) && (TIComms.message[0] == 0 || TIComms.message[0] == 1)){
    //     /**
    //      * TIComms.message[0] == 0 -> Ready To Go 
    //      * TIComms.message[0] == 1 -> Going 
    //     */
    //     appsHandler.readSensorVal(); //read in APPS 
    //     uint8_t mappedValue = 0;
    //     if(appsHandler.getMappedSensorVal(&mappedValue)){
    //         APPSComms.message[0] = mappedValue;
    //     }
    //     else{
    //         mappedValue = -1; 
    //         //define an impossible mapped value to trigger error message to throttleinterlock 
    //         APPSComms.message[0] = mappedValue; 
    //     }
    // }
    delay(DELAY_MS);
}

