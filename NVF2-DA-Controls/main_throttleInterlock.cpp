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

#include <NVF2-Can/CanBus/NVF_Can.h>

StateMachine stateMachine;
CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;

//FIRST CAN Network
MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_Can NVFCan0(&NVFCanI0, CommsDef::THROTTLEINTERLOCK_CAN_ID);
can_frame rxBuf0;
can_frame txBuf0;

//Second CAN Network
MCP_CAN NVFCanI1(BoardDef::PIN_CANSPI_CSN2);
NVF_Can NVFCan1(&NVFCanI1, CommsDef::THROTTLEINTERLOCK_CAN_ID);
can_frame rxBuf1;
can_frame txBuf1;

systemComms_t APPS1Comms;
systemComms_t APPS2Comms;
systemComms_t BPPC1Comms;
systemComms_t BPPC2Comms;
systemComms_t R2DComms; 
// systemComms_t TIComms;

void setup()
{
    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    throttleInterlock = ThrottleInterlock(&stateMachine);

    NVFCan0.setup();
    NVFCan1.setup();

    // define buffers for comms that i want to interact with
    // APPS1Comms = systemComms_t (0, CommsDef::APPS1_CAN_ID, -1, -1, (can_frame){});
    // APPS2Comms = systemComms_t (0, CommsDef::APPS2_CAN_ID, -1, -1, (can_frame){});
    // BPPC1Comms = systemComms_t (0, CommsDef::BPPC1_CAN_ID, -1, -1, (can_frame){});
    // BPPC2Comms = systemComms_t (0, CommsDef::BPPC2_CAN_ID, -1, -1, (can_frame){});
    // Initialize the systemComms_t instances with their can_frame members

    APPS1Comms.comms_id = CommsDef::APPS1_CAN_ID;
    APPS1Comms.tValidHeartbeat = -1;
    APPS1Comms.tSinceValidHeartbeatMs = -1;
    APPS1Comms.frame.can_id = 0;
    APPS1Comms.frame.can_dlc = 0;
    memset(APPS1Comms.frame.data, 0, sizeof(APPS1Comms.frame.data));

    APPS2Comms.comms_id = CommsDef::APPS2_CAN_ID;
    APPS2Comms.tValidHeartbeat = -1;
    APPS2Comms.tSinceValidHeartbeatMs = -1;
    APPS2Comms.frame.can_id = 0;
    APPS2Comms.frame.can_dlc = 0;
    memset(APPS2Comms.frame.data, 0, sizeof(APPS2Comms.frame.data));

    BPPC1Comms.comms_id = CommsDef::BPPC1_CAN_ID;
    BPPC1Comms.tValidHeartbeat = -1;
    BPPC1Comms.tSinceValidHeartbeatMs = -1;
    BPPC1Comms.frame.can_id = 0;
    BPPC1Comms.frame.can_dlc = 0;
    memset(BPPC1Comms.frame.data, 0, sizeof(BPPC1Comms.frame.data));

    BPPC2Comms.comms_id = CommsDef::BPPC2_CAN_ID;
    BPPC2Comms.tValidHeartbeat = -1;
    BPPC2Comms.tSinceValidHeartbeatMs = -1;
    BPPC2Comms.frame.can_id = 0;
    BPPC2Comms.frame.can_dlc = 0;
    memset(BPPC2Comms.frame.data, 0, sizeof(BPPC2Comms.frame.data));

    R2DComms.comms_id = CommsDef::R2D_CAN_ID;
    R2DComms.tValidHeartbeat = -1;
    R2DComms.tSinceValidHeartbeatMs = -1;
    R2DComms.frame.can_id = 0;
    R2DComms.frame.can_dlc = 0;
    memset(R2DComms.frame.data, 0, sizeof(R2DComms.frame.data));
}


void loop()
{   
    // get can frame
    if (NVFCan0.taskLoopRecv(&rxBuf0))
    {
        if (commsHandler.trnsBuf(&APPS1Comms, &rxBuf0)){}
        else if (commsHandler.trnsBuf(&APPS2Comms, &rxBuf0)){}
        else if (commsHandler.trnsBuf(&BPPC1Comms, &rxBuf0)){}
        else if (commsHandler.trnsBuf(&BPPC2Comms, &rxBuf0)){}
        else if (commsHandler.trnsBuf(&R2DComms, &rxBuf0)){}
        else {/*message not for target*/}
    }

    // get statuses
    commsHandler.taskHeartbeatCheck(&APPS1Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&APPS2Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&APPS1Comms, &APPS2Comms, CAR_STOP_CONDITIONS::APPS_INVALID);

    commsHandler.taskHeartbeatCheck(&BPPC1Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&BPPC1Comms, &BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_INVALID);

    commsHandler.taskHeartbeatCheck(&R2DComms, CAR_STOP_CONDITIONS::R2D_HEARTBEAT_LOSS);

    //check for R2D state 
    if (R2DComms.frame.data[0] == 0xEE && stateMachine.getCarState() == (uint8_t) 3){
        stateMachine.setCarStateReady();
    }

    throttleInterlock.taskThrottleInterlock();

    // aggregate throttle values
    {
        /***
         * perform checks ie.
         * if brake pressed, throttle = 0
         * if implausible, throttle = 0
         * ...
        */
        // 
        // throttle = avg(APPS1Comms.%, APPS2Comms.%)
    }

    txBuf0.data[0] = (uint8_t) stateMachine.getCarState();
    txBuf0.data[1] = (uint8_t) stateMachine.getCarStopReason();
    // txBuf0.data[2] = throttle; ...
    // txBuf0.dlc = ?
    if (!NVFCan0.tx(&txBuf0)) { /* msg didnt send */ }

    // rx and process rxbuf1 from network 2
    // txBuf1.data[] ... = throttle ... 
    // txBuf1.dlc = ?
    if (!NVFCan1.tx(&txBuf1)) { /* msg didnt send */ }
    

    // NO_DELAY
}