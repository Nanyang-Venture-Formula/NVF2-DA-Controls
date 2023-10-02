/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** stateMachine
*/

#include "stateMachine.h"

/**
 * @brief Construct a new State Machine:: State Machine object
 *
 */
StateMachine::StateMachine()
{
    carState = CAR_STATES::STOPPED;
    carStopReason = CAR_STOP_CONDITIONS::STARTUP;
}

/**
 * @brief
 *
 * @return CAR_STATES
 */
CAR_STATES StateMachine::getCarState(void)
{
    return this->carState;
}

/**
 * @brief
 *
 * @param carState
 */
void StateMachine::setCarState(CAR_STATES carState)
{
    this->carState = carState;
}

/**
 *
 */
void StateMachine::setCarStateStop(CAR_STOP_CONDITIONS carStopReason)
{
    this->setCarState(CAR_STATES::STOP);
    this->setCarStopReason(carStopReason);
}

/**
 * @brief
 *
 */
void StateMachine::setCarStateStopped(void)
{
    this->setCarState(CAR_STATES::STOPPED);
}

/**
 * @brief
 *
 */
void StateMachine::setCarStateReady(void)
{
    this->setCarState(CAR_STATES::STOPPED);
    this->setCarStopReason(CAR_STOP_CONDITIONS::NA);
}

/**
 * @brief
 *
 */
void StateMachine::setCarStateGoing(void)
{
    this->setCarState(CAR_STATES::GOING);
}

/**
 * @brief
 *
 * @return CAR_STOP_CONDITIONS
 */
CAR_STOP_CONDITIONS StateMachine::getCarStopReason(void)
{
    return this->carStopReason;
}

/**
 * @brief
 *
 * @param carStopReason
 */
void StateMachine::setCarStopReason(CAR_STOP_CONDITIONS carStopReason)
{
    this->carStopReason = carStopReason;
}

/**
 * @brief
 * @note
 * copy status code of car to uint8_t*
 */
void StateMachine::getCarStatusCode(uint8_t *pStatusCode)
{
    uint8_t u8carState = (uint8_t)this->carState;
    uint8_t u8carStopReason = (uint8_t)this->carStopReason;

    uint8_t u8carStatusCode = (u8carState << 4) | u8carStopReason;
    *pStatusCode = u8carStatusCode;
}
