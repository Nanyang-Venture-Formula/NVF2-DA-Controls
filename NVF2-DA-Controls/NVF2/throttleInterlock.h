/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF_DA_StateMachine
** File description:
** throttleInterlock
*/

#ifndef THROTTLEINTERLOCK_H_
#define THROTTLEINTERLOCK_H_

#include "stateMachine.h"

namespace ns_throttleInterlock
{
    class ThrottleInterlock
    {
        private:
            ns_stateMachine::StateMachine* pStateMachine;

        public:
            ThrottleInterlock(ns_stateMachine::StateMachine*);
            
            void taskThrottleInterlock();
    };
}

#endif /* !THROTTLEINTERLOCK_H_ */
