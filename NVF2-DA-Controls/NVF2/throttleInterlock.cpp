/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** throttleInterlock
*/

#include "throttleInterlock.h"

using namespace ns_throttleInterlock;

/**
 * @brief Construct a new Throttle Interlock:: Throttle Interlock object
 * 
 * @param pStateMachine 
 */
ThrottleInterlock::ThrottleInterlock(ns_stateMachine::StateMachine* pStateMachine)
{
    this->pStateMachine = pStateMachine;
}

void ThrottleInterlock::taskThrottleInterlock()
{
    if (pStateMachine->getCarState() == ns_stateMachine::CAR_STATES::READY_2_GO)
    {
        // Activate AIR, close circuit, supply poweer to motors
    }

}
