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

MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN1);
NVF_Can NVFCan0(&NVFCanI0, CommsDef::THROTTLEINTERLOCK1_CAN_ID);

StateMachine stateMachine;
CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;

systemComms_t APPS1Comms;
systemComms_t APPS2Comms;
systemComms_t BPPC1Comms;
systemComms_t BPPC2Comms;

can_frame rx_buf;
can_frame tx_buf;
uint8_t carStatusBuf;

void setup()
{
    SerialUSB.begin(115200);
    Serial1.begin(115200);

    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    throttleInterlock = ThrottleInterlock(&stateMachine);

    // commsHandler.begin();
    // commsHandler.CAN_begin(CommsDef::THROTTLEINTERLOCK_CAN_ID, BoardDef::PIN_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    APPS1Comms = systemComms_t();
    APPS2Comms = systemComms_t();
    BPPC1Comms = systemComms_t();
    BPPC2Comms = systemComms_t();

    APPS1Comms.comms_id = CommsDef::APPS1_CAN_ID;
    APPS2Comms.comms_id = CommsDef::APPS2_CAN_ID;
    BPPC1Comms.comms_id = CommsDef::BPPC1_CAN_ID;
    BPPC2Comms.comms_id = CommsDef::BPPC2_CAN_ID;
}

void loop()
{
    // recieve CAN buffer
    if(NVFCan0.taskLoopRecv())
    {
        if      (commsHandler.CAN_transBuf(&APPS1Comms, &rx_buf)) {}
        else if (commsHandler.CAN_transBuf(&APPS2Comms, &rx_buf)) {}
        else if (commsHandler.CAN_transBuf(&BPPC1Comms, &rx_buf)) {}
        else if (commsHandler.CAN_transBuf(&BPPC2Comms, &rx_buf)) {}
    }

    // get statuses
    commsHandler.taskHeartbeatCheck(&APPS1Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&APPS2Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&APPS1Comms, &APPS2Comms, CAR_STOP_CONDITIONS::APPS_INVALID);

    commsHandler.taskHeartbeatCheck(&BPPC1Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskHeartbeatCheck(&BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    commsHandler.taskImplausiblyCheck(&BPPC1Comms, &BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_INVALID);

    throttleInterlock.taskThrottleInterlock();

    // todo send CAN tx to report stateMachine carState
    stateMachine.getCarStatusCode(&carStatusBuf);
    tx_buf.data[0] = 0xFF;
    tx_buf.data[1] = carStatusBuf;
    tx_buf.can_dlc = 2;

    NVFCan0.tx(tx_buf);
}
