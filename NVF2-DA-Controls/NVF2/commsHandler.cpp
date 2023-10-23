/*
** NANYANG VENTURE FORMULA RACING, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#include "commsHandler.h"
uint32_t apps_time = 0;

CommsHandler::CommsHandler(StateMachine *pStateMachine)
{
   this->pStateMachine = pStateMachine;
   this->canInterface = new MCP_CAN(BoardDef::PIN_CANSPI_CSN);
    
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


bool CommsHandler::Serial_begin(uint8_t br, HardwareSerial *pSerial)
{
    this->pSerial = pSerial;
    this->pSerial->begin(br);
    return 1;
}


bool CommsHandler::SerialTX()
{
    return 1;
}

bool CommsHandler::SerialRX()
{
    return 1;
}


bool CommsHandler::CAN_begin(uint32_t CanID, uint16_t CS_Pin)
{
    this->canId = CanID;
    SPI.begin();
    while (CAN_OK != this->canInterface->begin(MCP_ANY, CommsDef::CAN_SPEED, MCP_8MHZ))
    {
        return 0;
    }
    this->canInterface->setMode(MCP_NORMAL);
    return 1;
}


bool CommsHandler::CAN_TX(systemComms_t* pCommsInterface)
{
    uint8_t ret = this->canInterface->sendMsgBuf(pCommsInterface->comms_id, 
    pCommsInterface->dataLength, pCommsInterface->message);
    return (ret == CAN_OK);
}

/**
 * recieved data only from the desired CAN ID 
 * store the recieved data in the parameter receivedData 
 * ASSUMPTION: all data received is in int form 
*/

bool CommsHandler::CAN_RX(systemComms_t* pCommsInterface)
{
    if(this->canInterface->checkReceive() == CAN_MSGAVAIL)
    {   
        this->canInterface->readMsgBuf(&this->canMsgBuf.can_id, &this->canMsgBuf.can_dlc, this->canMsgBuf.data);
        // this->canMsgBuf.can_id = this->canInterface->getCanId();
        if (this->canMsgBuf.can_id == pCommsInterface->comms_id){
            for(int i = 0; i < pCommsInterface->dataLength; i++){
                pCommsInterface->message[i] = *this->canMsgBuf.data;  
            }
            pCommsInterface->tValidHeartbeat = millis();
            pCommsInterface->tSinceValidHeartbeatMs = millis() - pCommsInterface->tValidHeartbeat; 
            return 1;    
        }
    }
    return 0;
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
    //will one of the value be negative since both is inverse to each other 
    // if yes maybe use mapped data, check I not sure if val1 & val2 refers to mapped or raw 

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
