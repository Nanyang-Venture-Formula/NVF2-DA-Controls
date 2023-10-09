/*
** NANYANG VENTURE FORMULA RACING, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#include "commsHandler.h"

CommsHandler::CommsHandler(StateMachine *pStateMachine)
{
    
}

bool CommsHandler::SerialTX()
{
    return 1;
}

bool CommsHandler::SerialRX()
{
    return 1;
}

bool CommsHandler::CAN_TX(can_frame*)
{
    
    return 1;
}

bool CommsHandler::CAN_RX()
{
    if(CAN_MSGAVAIL == this->canInterface->checkReceive())
    {
        this->canInterface->readMsgBuf(&this->canMsgBuf.can_id, &this->canMsgBuf.can_dlc, this->canMsgBuf.data);
        // this->canMsgBuf.can_id = this->canInterface->getCanId();

        return 1;
    }

    return 0;
}

bool CommsHandler::begin()
{
    if (this->pStateMachine == nullptr) 
    {
        return 0;
    }

    this->isInit = 1;
    return 1;
}

bool CommsHandler::CAN_begin(uint32_t CanID, uint16_t CS_Pin)
{
    this->canId = CanID;
    // SPI.begin(SCK, MISO, MOSI, CS_Pin);
    if (CAN_OK != this->canInterface->begin(MCP_ANY, CommsDef::CAN_SPEED, MCP_8MHZ))
    {
        return 0;
    }
    this->canInterface->setMode(MCP_NORMAL);

    return 1;
}

bool CommsHandler::Serial_begin(uint8_t br, HardwareSerial *pSerial)
{
    this->pSerial = pSerial;
    this->pSerial->begin(br);
    return 1;
}

/**
 * @brief 
 * 
 * @param commsInterface 
 * @param stopReasonIfFailed 
 */
void CommsHandler::taskHeartbeatCheck(
    systemComms_t* pCommsInterface,
    CAR_STOP_CONDITIONS stopReasonIfFailed
    // CAR_STOP_CONDITIONS stopReasonIfFailed = CAR_STOP_CONDITIONS::NA /* prep for pair testing */
    )
{
    if (this->pStateMachine->getCarStopReason() == CAR_STOP_CONDITIONS::STARTUP)
    {
        // car startup, need reboot
    }
    else if (tAcceptableHeartbeatLossMs <= pCommsInterface->tSinceValidHeartbeatMs)
    {
        this->pStateMachine->setCarStateStop(stopReasonIfFailed);
    }
}

/**
 * @brief 
 * 
 * @param pCommsInterface1 
 * @param pCommsInterface2 
 * @param stopReasonIfFailed 
 * 
 * @note
 * this function checks if APPS/BPPC pair value are valid
 * stopReasonIfFailed should only be APPS_INVALID OR BPPC_INVALID
 */
void CommsHandler::taskImplausiblyCheck(
    systemComms_t* pCommsInterface1,
    systemComms_t* pCommsInterface2,
    CAR_STOP_CONDITIONS stopReasonIfFailed
    )
{
    bool isValid = 0;
    uint8_t *data_1 = pCommsInterface1->message; 
    uint8_t *data_2 = pCommsInterface2->message;

    uint8_t val1 = data_1[0];
    uint8_t val2 = data_2[0];

    //calculate 
    uint64_t absoluteDifference = (val1 > val2) ? (val1-val2):(val2-val1);
    uint64_t threshold1 = (0.1*val1);
    uint64_t threshold2 = (0.1*val2);
    isValid = (absoluteDifference<threshold1 && absoluteDifference<threshold2);

    if (!isValid)
    {
        this->pStateMachine->setCarStateStop(stopReasonIfFailed);
    }
}
