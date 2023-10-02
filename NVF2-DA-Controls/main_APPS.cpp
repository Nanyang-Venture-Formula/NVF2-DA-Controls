/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_APPS
*/

#include <Arduino.h>
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"
#include "NVF2/boardDef.h"

CommsHandler commsHandler;
systemComms_t TIComms;

void setup()
{
    Serial.begin(115200);

    commsHandler = CommsHandler();
    commsHandler.begin();
    // todo make this dynamic
    commsHandler.CAN_begin(CommsDef::APPS1_CAN_ID, BoardDef::PI_PICO_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    TIComms = systemComms_t();
    TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;
}

void loop()
{
    /**
     * @todo
     * @pseudocode
     * 
     * if calibrate mode
     * calibrate and sync with other APPS sensors 
     */

    // recieve CAN buffer
    commsHandler.CAN_RX();

    /**
     * @todo
     * @pseudocode
     * 
     * hardwarehandler.getSensorValue()
     * hardwarehandler.getMappedSensorValue()
     * send sensor value
     */

    // todo send CAN tx to report stateMachine carState
    commsHandler.CAN_TX();
}
