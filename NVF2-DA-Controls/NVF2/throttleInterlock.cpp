/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** throttleInterlock
*/

#include "throttleInterlock.h"

/**
 * @brief Construct a new Throttle Interlock:: Throttle Interlock object
 *
 * @param pStateMachine
 */
ThrottleInterlock::ThrottleInterlock(StateMachine *pStateMachine)
{
    this->pStateMachine = pStateMachine;
}

void ThrottleInterlock::taskThrottleInterlock()
{
    if (pStateMachine->getCarState() == CAR_STATES::READY_2_GO)
    {
        // Activate AIR, close circuit, supply poweer to motors
    }
}
