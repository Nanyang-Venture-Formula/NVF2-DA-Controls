/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** commsListener
*/

#include "commsListener.h"

using namespace ns_communications;

/**
 * @brief Construct a new Comms Listener:: Comms Listener object
 * 
 * @param pStateMachine 
 */
CommsListener::CommsListener(ns_stateMachine::StateMachine* pStateMachine)
{
    this->pStateMachine = pStateMachine;
}

/**
 * @brief 
 * 
 * @param commsInterface 
 * @param stopReasonIfFailed 
 */
void CommsListener::taskHeartbeatCheck(
    systemComms_t* pCommsInterface,
    ns_stateMachine::CAR_STOP_CONDITIONS stopReasonIfFailed
    // CAR_STOP_CONDITIONS stopReasonIfFailed = CAR_STOP_CONDITIONS::NA /* prep for pair testing */
    )
{
    if (this->pStateMachine->getCarStopReason() == ns_stateMachine::CAR_STOP_CONDITIONS::STARTUP)
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
void CommsListener::taskImplausiblyCheck(
    systemComms_t* pCommsInterface1,
    systemComms_t* pCommsInterface2,
    ns_stateMachine::CAR_STOP_CONDITIONS stopReasonIfFailed
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
