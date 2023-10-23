/*
** NANYANG VENTURE FORMULA RACING, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#ifndef COMMSHANDLER_H_
#define COMMSHANDLER_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <mcp_can.h>
#include "stdint.h"
#include "time.h"

#include "stateMachine.h"
#include "commsDef.h"
#include "boardDef.h"

#define numberCommsInterfaces 5
#define tAcceptableHeartbeatLossMs 10.0

struct can_frame 
{
  unsigned long can_id; 
  uint8_t can_dlc;      
  uint8_t data[8];
};

struct systemComms_t
{
    bool initiated = 0;
    uint16_t comms_id;
    time_t tValidHeartbeat;
    double tSinceValidHeartbeatMs;
    uint8_t dataLength;
    uint8_t message[8];
};

class CommsHandler
{
private:
    StateMachine *pStateMachine;
    bool isInit = 0;

    HardwareSerial *pSerial;
    uint32_t canId;

    MCP_CAN *canInterface;
    // buffers
    can_frame canMsgBuf;

public:
    CommsHandler(StateMachine * = nullptr);

    bool begin();

    void taskHeartbeatCheck(systemComms_t *, CAR_STOP_CONDITIONS);
    void taskImplausiblyCheck(systemComms_t *, systemComms_t *, CAR_STOP_CONDITIONS);

    bool CAN_begin(uint32_t, uint16_t);
    bool CAN_TX(systemComms_t*);
    bool CAN_RX(systemComms_t* pCommsInterface);

    bool Serial_begin(uint8_t, HardwareSerial * = &Serial);
    bool SerialTX();
    bool SerialRX();
};

#endif /* !COMMSHANDLER_H_ */
