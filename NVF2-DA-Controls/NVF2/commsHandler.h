/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#ifndef COMMSHANDLER_H_
#define COMMSHANDLER_H_

#include "stdint.h"
#include "time.h"

#include "stateMachine.h"

#define numberCommsInterfaces 5
#define tAcceptableHeartbeatLossMs 10.0

struct systemComms_t
{
    bool initiated = 0;
    uint16_t comms_id;
    time_t tValidHeartbeat;
    double tSinceValidHeartbeatMs;
    uint64_t message;
};

class CommsHandler
{
private:
    StateMachine *pStateMachine;
    bool isInit = 0;

    uint32_t canId;

public:
    CommsHandler(StateMachine * = nullptr);

    bool begin();

    void taskHeartbeatCheck(systemComms_t *, CAR_STOP_CONDITIONS);
    void taskImplausiblyCheck(systemComms_t *, systemComms_t *, CAR_STOP_CONDITIONS);

    bool CAN_begin(uint32_t, uint16_t);
    bool CAN_TX() {}
    bool CAN_RX() {}

    bool SerialTX() {}
    bool SerialRX() {}
};

#endif /* !COMMSHANDLER_H_ */
