/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** throttleInterlock
*/

#include "NVF2/throttleInterlock.h"

/**
 * @brief Construct a new Throttle Interlock:: Throttle Interlock object
 *
 * @param pStateMachine
 */
ThrottleInterlock::ThrottleInterlock(StateMachine *pStateMachine)
{
    this->pStateMachine = pStateMachine;
    // this->pHardwareHandler = pHardwareHandler;
}


bool ThrottleInterlock::begin()
{
    pinMode(BoardDef::PIN_AIR_TRIGGER_OUT, OUTPUT);
    return 1;
}


void ThrottleInterlock::taskThrottleInterlock()
{
    CAR_STATES carState = pStateMachine->getCarState();
    switch (carState)
    {
    case CAR_STATES::GOING:
    {
    }
    case CAR_STATES::READY_2_GO:
    {
        // Activate AIR, close circuit, supply power to motors
        digitalWrite(BoardDef::PIN_AIR_TRIGGER_OUT, 1);
        break;
    }
    case CAR_STATES::STOP:
    {
    }
    case CAR_STATES::STOPPED:
    {
        digitalWrite(BoardDef::PIN_AIR_TRIGGER_OUT, 0);
        break;
    }
    }
}

