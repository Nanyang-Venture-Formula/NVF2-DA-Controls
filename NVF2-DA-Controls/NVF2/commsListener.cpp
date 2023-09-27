/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** commsListener
*/

#include "stateMachine.h"

using namespace ns_stateMachine;

/**
 * @brief Construct a new Comms Listener:: Comms Listener object
 * 
 * @param pStateMachine 
 */
ns_stateMachine::CommsListener::CommsListener(StateMachine* pStateMachine)
{
    this->pStateMachine = pStateMachine;
}

/**
 * @brief 
 * 
 * @param commsInterface 
 * @param stopReasonIfFailed 
 */
void ns_stateMachine::CommsListener::taskHeartbeatCheck(
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
void ns_stateMachine::CommsListener::taskImplausiblyCheck(
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
