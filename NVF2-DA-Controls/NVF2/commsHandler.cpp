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

bool CommsHandler::begin()
{
    if (this->pStateMachine == nullptr) {
        return 0;
    }

    this->isInit = 1;
    return 1;
}

bool CommsHandler::CAN_begin(uint32_t CanID, uint16_t CS_Pin)
{
    this->canId = CanID;
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
    // pCommsInterface1->message;
    // pCommsInterface2->message;

    // todo read values and perform ImplausiblyCheck
    

    // if not valid signal, tell statemachine to stop
    if (!isValid)
    {
        this->pStateMachine->setCarStateStop(stopReasonIfFailed);
    }
}
