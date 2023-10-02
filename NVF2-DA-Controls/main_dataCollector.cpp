/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_dataCollector
*/

#include <Arduino.h>

#include "NVF2/boardDef.h"
#include "NVF2/stateMachine.h"
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"

StateMachine stateMachine;
CommsHandler commsHandler;

systemComms_t TIComms;

void setupDisp(void) {}
void dispStatus(void) {}
void reportStatus(void) {}

/**
 * @brief data collector node serves multiple purposes:
 * 1. show status codes of car on 7 segment display (debug in early times without need of screen)
 * 2. when connected to SBC, will translate comms (ie. CANBUS) to SBC for data collection and processing
 *
 */

void setup()
{
    SerialUSB.begin(115200);
    Serial1.begin(115200);

    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);

    commsHandler.begin();
    commsHandler.CAN_begin(CommsDef::DATACOLLECTOR_CAN_ID, BoardDef::PIN_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    TIComms = systemComms_t();
    TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;
}

void loop()
{
    // get statuses
    commsHandler.taskHeartbeatCheck(&TIComms, CAR_STOP_CONDITIONS::T_HEARTBEAT_LOSS);

    //todo take over and transmit change of stateMachine owner to dataCollector
    //todo tx over CANBus that Car will stop due to loss of T_Heartbeat

    // report to disp
    // dispStatus();

    // report to SBC
    // reportStatus();
}
