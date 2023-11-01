/*
** NANYANG VENTURE FORMULA RACING, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#include "commsHandler.h"
#include <time.h>

uint32_t apps_time = 0;
uint32_t systemComms_t::comms_id = 0;

CommsHandler::CommsHandler(StateMachine *pStateMachine)
{
   this->pStateMachine = pStateMachine;
//    this->canInterface = new MCP_CAN(BoardDef::PIN_CANSPI_CSN);
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

/**
 * @brief
 * @param comsInterface
 * @param CAN_frame
 * copy message from buf 
 * return true if same id
*/
bool CommsHandler::trnsBuf(systemComms_t* pCommsInterface, can_frame* buf)
{
    if (buf->can_id == pCommsInterface->comms_id)
    {
        pCommsInterface->frame.can_id = buf->can_id;
        pCommsInterface->frame.can_dlc = buf->can_dlc;
        memcpy(pCommsInterface->frame.data, buf->data, sizeof(buf->data));
        
        pCommsInterface->tValidHeartbeat = millis();
        return 1;
    }
    else{
        return 0;
    }
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
    pCommsInterface->tSinceValidHeartbeatMs =   millis() - pCommsInterface->tValidHeartbeat;

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
    uint8_t *data_1 = pCommsInterface1->frame.data; 
    uint8_t *data_2 = pCommsInterface2->frame.data;

    uint8_t val1 = data_1[0];
    uint8_t val2 = data_2[0]; 
    
    //calculate 
    uint64_t absoluteDifference = (val1 > val2) ? (val1-val2):(val2-val1);
    uint64_t threshold1 = (0.1*val1);
    uint64_t threshold2 = (0.1*val2);
    isValid = (absoluteDifference<threshold1 && absoluteDifference<threshold2);

    if (isValid){
        apps_time = 0;
    }
    else{
        if (apps_time == 0){
            apps_time = millis();
        }
        else{
            if (millis() - apps_time > 100){
                this->pStateMachine->setCarStateStop(stopReasonIfFailed);
            }
        }
    }
}
