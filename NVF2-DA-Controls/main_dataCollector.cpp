#include <Arduino.h>

#include "NVF2/stateMachine.h"

const uint16_t BCD1_PINS[] = { 1, 2, 3, 4};
const uint16_t BCD2_PINS[] = { 5, 6, 7, 8};
const uint16_t SERIAL0_PINS[] = {9, 10};
const uint16_t CANBUS_PINS[] = {11, 12};

ns_stateMachine::StateMachine stateMachine;
ns_stateMachine::StateMachine *pStateMachine;
// ns_stateMachine::CommsListener commsListener;
// ns_stateMachine::CommsListener::CommsListener

ns_stateMachine::systemComms_t APPS1Comms;
ns_stateMachine::systemComms_t *pAPPS1Comms;
// ns_stateMachine::systemComms_t APPS2Comms;
// ns_stateMachine::systemComms_t *pAPPS2Comms;

// ns_stateMachine::systemComms_t BPPC1Comms;
// ns_stateMachine::systemComms_t *pBPPC1Comms;
// ns_stateMachine::systemComms_t BPPC2Comms;
// ns_stateMachine::systemComms_t *pBPPC2Comms;


void setupDisp(void) {}
void dispStatus(void) {}
void reportStatus(void) {}

/**
 * @brief data collector node serves multiple purposes:
 * 1. show status codes of car on 7 segment display (debug in early times without need of screen)
 * 2. when connected to SBC, will translate comms (ie. CANBUS) to SBC for data collection and processing
 * 
 */

void setup() {

    setupDisp();
    SerialUSB.begin(115200);
    Serial1.begin(115200);

    stateMachine = ns_stateMachine::StateMachine();
    pStateMachine = &stateMachine;

    // commsListener = ns_stateMachine::CommsListener(pStateMachine);

    APPS1Comms = ns_stateMachine::systemComms_t();
    pAPPS1Comms = &APPS1Comms;
    pAPPS1Comms->comms_id = 0xAF00;

    // APPS2Comms = ns_stateMachine::systemComms_t();
    // pAPPS2Comms = &APPS2Comms;
    // pAPPS2Comms->comms_id = 0xAF01;

    // BPPC1Comms = ns_stateMachine::systemComms_t();
    // pBPPC1Comms = &BPPC1Comms;
    // pBPPC1Comms->comms_id = 0xAE00;

    // BPPC2Comms = ns_stateMachine::systemComms_t();
    // pBPPC2Comms = &BPPC2Comms;
    // pBPPC2Comms->comms_id = 0xAE01;
}

void loop() {
    // get statuses
    // pCommsListener->taskHeartbeatCheck(pAPPS1Comms, ns_stateMachine::CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    // pCommsListener->taskHeartbeatCheck(pAPPS2Comms, ns_stateMachine::CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    // pCommsListener->taskImplausiblyCheck(pAPPS1Comms, pAPPS2Comms, ns_stateMachine::CAR_STOP_CONDITIONS::APPS_INVALID);

    // pCommsListener->taskHeartbeatCheck(pBPPC1Comms, ns_stateMachine::CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    // pCommsListener->taskHeartbeatCheck(pBPPC2Comms, ns_stateMachine::CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    // pCommsListener->taskImplausiblyCheck(pBPPC1Comms, pBPPC2Comms, ns_stateMachine::CAR_STOP_CONDITIONS::BPPC_INVALID);

    // report to disp
    dispStatus();

    // report to SBC
    reportStatus();
}
