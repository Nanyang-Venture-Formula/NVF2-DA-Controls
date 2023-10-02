/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_throttleInterlock
*/

#include <Arduino.h>
#include "NVF2/stateMachine.h"
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"

StateMachine stateMachine;
CommsHandler commsHandler;

systemComms_t APPS1Comms;
systemComms_t APPS2Comms;

// systemComms_t BPPC1Comms;
// systemComms_t *pBPPC1Comms;
// systemComms_t BPPC2Comms;
// systemComms_t *pBPPC2Comms;

void setup()
{
    SerialUSB.begin(115200);
    Serial1.begin(115200);

    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);

    commsHandler.begin();
    commsHandler.CAN_begin(CommsDef::THROTTLEINTERLOCK_CAN_ID, 10);

    APPS1Comms = systemComms_t();
    APPS1Comms.comms_id = CommsDef::APPS1_CAN_ID;

    APPS2Comms = systemComms_t();
    APPS2Comms.comms_id = CommsDef::APPS2_CAN_ID;
}

void loop()
{
    // get statuses
    commsHandler.taskHeartbeatCheck(&APPS1Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&APPS2Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&APPS1Comms, &APPS2Comms, CAR_STOP_CONDITIONS::APPS_INVALID);

    // todo send CAN tx to report stateMachine carState
    commsHandler.CAN_TX();
}
