/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_throttleInterlock
*/

#include <Arduino.h>
#include "NVF2/stateMachine.h"
#include "NVF2/throttleInterlock.h"
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"
#include "NVF2/boardDef.h"

StateMachine stateMachine;
CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;

// can_frame rxBuf

systemComms_t APPS1Comms;
systemComms_t APPS2Comms;
systemComms_t BPPC1Comms;
systemComms_t BPPC2Comms;
systemComms_t TIComms;
void setup()
{
    //SerialUSB.begin(115200);
    //Serial1.begin(115200);

    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    throttleInterlock = ThrottleInterlock(&stateMachine);

    // commsHandler.begin();
    // commsHandler.CAN_begin(CommsDef::THROTTLEINTERLOCK_CAN_ID, BoardDef::PIN_CANSPI_CSN);

    // NVFCan.begin

    // define buffers for comms that i want to interact with
    APPS1Comms = (systemComms_t) {0, CommsDef::APPS1_CAN_ID, 0, -1, (can_frame) };
    APPS2Comms = systemComms_t();
    BPPC1Comms = systemComms_t();
    BPPC2Comms = systemComms_t();
}


void loop()
{   
    if(this->canInterface->checkReceive() == CAN_MSGAVAIL)
    {
        // get can frame
        can_rx(&rxBuf);

        if (0)
        else if (commsHandler.trnsfBuf(&APPS1Comms, &rxBuf))
        else if (commsHandler.trnsfBuf(&APPS2Comms, &rxBuf))
        else if (commsHandler.trnsfBuf(&BPPC1Comms, &rxBuf))
        else if (commsHandler.trnsfBuf(&BPPC2Comms, &rxBuf))
        else
        {
            // message not for target
        }
    }

    // get statuses
    commsHandler.taskHeartbeatCheck(&APPS1Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&APPS2Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&APPS1Comms, &APPS2Comms, CAR_STOP_CONDITIONS::APPS_INVALID);

    commsHandler.taskHeartbeatCheck(&BPPC1Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&BPPC1Comms, &BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_INVALID);

    throttleInterlock.taskThrottleInterlock();
    CAR_STATES carState = stateMachine.getCarState();

    // Set the CAR_STATES value in the message array
    // TIComms.message[0] = static_cast<uint8_t>(carState);

    // Use the CAN_TX method to send the updated systemComms_t structure
    // commsHandler.CAN_TX(&TIComms);
    // todo send CAN tx to report stateMachine carState
    //commsHandler.CAN_TX();

    txBuf.data[0] = (uint8_t) stateMachine.getCarState();
    txBuf.data[1] = (uint8_t) stateMachine.getCarStopReason();
    if (!NVFCan0.tx(&txBuf))
    {
        // msg didnt send
    }

    // NO_DELAY
}
