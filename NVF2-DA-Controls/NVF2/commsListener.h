/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** commsListener
*/

#ifndef COMMSLISTENER_H_
#define COMMSLISTENER_H_

#include "stdint.h"
#include "time.h"

#include "stateMachine.h"

#define numberCommsInterfaces       5
#define tAcceptableHeartbeatLossMs  10.0


namespace ns_communications
{
    struct systemComms_t
    {
        bool        initiated = 0;
        uint16_t    comms_id;
        time_t      tValidHeartbeat;
        double      tSinceValidHeartbeatMs;
        uint64_t    message;
    };

    class CommsListener
    {
        private:
            // this is an array of pointers of commsInterfaces
            // systemComms_t commsInterfaces[numberCommsInterfaces];
            ns_stateMachine::StateMachine* pStateMachine;

        public:
            CommsListener(ns_stateMachine::StateMachine*);
            CommsListener();

            void taskHeartbeatCheck(systemComms_t*, ns_stateMachine::CAR_STOP_CONDITIONS);
            void taskImplausiblyCheck(systemComms_t*, systemComms_t*, ns_stateMachine::CAR_STOP_CONDITIONS);

            /**
             * @brief 
             * 
             */
            // void serialMessageInterrupt(void)
            // {
            //     // stub value, replace with len of commsInterface arr len
            //     int num_comms = numberCommsInterfaces;
            //     uint64_t msg = 0xFA; // test message that R2D valid
            //     uint16_t msg_comms_id = 0xFA;

            //     /**
            //      * for each comms in listener;
            //      * if id of comms called, record message/ heartbeat
            //      */
            //     for (int i = 0; i < num_comms; i++)
            //     {
            //         if (commsInterfaces[i].comms_id = msg_comms_id)
            //         {
            //             commsInterfaces[i].tValidHeartbeat = time(0);
            //             commsInterfaces[i].message = msg;
            //             break;
            //         }
            //     }
            // }
            
    };
}

#endif /* !COMMSLISTENER_H_ */
