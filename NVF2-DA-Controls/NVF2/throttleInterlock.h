/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** throttleInterlock
*/

#ifndef THROTTLEINTERLOCK_H_
#define THROTTLEINTERLOCK_H_

#include "stateMachine.h"

class ThrottleInterlock
{
private:
    StateMachine *pStateMachine;

public:
    ThrottleInterlock(StateMachine *);

    void taskThrottleInterlock();
};

#endif /* !THROTTLEINTERLOCK_H_ */
