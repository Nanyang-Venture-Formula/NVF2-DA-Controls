/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** stateMachine
*/

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "stdint.h"
#include "time.h"

enum CAR_STATES
{
    READY_2_GO,
    GOING,
    STOP,
    STOPPED
};

enum CAR_STOP_CONDITIONS
{
    /**
     * @brief NA
     * @note
     * no reasons for stop;
     * CAR_STOP_CONDITIONS::NA is mutually exclusive with
     * CAR_STATES::READY_2_GO && CAR_STATES::GOING
     *
     * CAR_STOP_CONDITIONS should be cleared BEFORE
     * CAR_STATES::READY_2_GO set
     *
     * check these conditions to ensure no error on states
     */
    NA,

    /**
     * @brief STARTUP
     * @note
     * car just STARTUP, waiting for systems to react
     */
    STARTUP,

    /**
     * @brief APPS_INVALID
     * @note
     * APPS plasibility check failed:
     * >= 10% difference
     */
    APPS_INVALID,

    /**
     * @brief APPS_HEARTBEAT_LOSS
     * @note
     * no signal from APPS for > 10ms
     */
    APPS_HEARTBEAT_LOSS,

    /**
     * @brief BPPC_INVALID
     * @note
     * BPPC plasibility check failed:
     * //todo
     */
    BPPC_INVALID,

    /**
     * @brief BPPC_HEARTBEAT_LOSS
     * @note
     * no signal from APPS for > 10ms
     */
    BPPC_HEARTBEAT_LOSS,

    /**
     * @brief T_HEARTBEAT_LOSS
     * @note
     * Throttle Interlock (decision maker P1) heartbeat loss ->
     * fallback to failsafe (data collector (decision maker P2)) to initiate shutdown
     */
    T_HEARTBEAT_LOSS,


    /**
     * @brief R2D_HEARTBEAT_LOSS
     * @note
     * no signal from R2D for > 10ms
     */
    R2D_HEARTBEAT_LOSS,

    /**
     * @brief E_STOP
     * @note
     * E_STOP conditions met/ physical e-stop triggered
     */
    E_STOP
};

class StateMachine
{
private:
    CAR_STATES carState;
    CAR_STOP_CONDITIONS carStopReason;

public:
    StateMachine();

    /** car states */
    CAR_STATES getCarState(void);
    void setCarState(CAR_STATES);
    void setCarStateStop(CAR_STOP_CONDITIONS);
    void setCarStateStopped(void);
    void setCarStateReady(void);
    void setCarStateGoing(void);
    /** car states */

    /** car stop reason */
    CAR_STOP_CONDITIONS getCarStopReason(void);
    void setCarStopReason(CAR_STOP_CONDITIONS);
    /** car stop reason */

    void getCarStatusCode(uint8_t *);
};

#endif /* !STATEMACHINE_H_ */
