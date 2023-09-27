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

#define numberCommsInterfaces       5
#define tAcceptableHeartbeatLossMs  10.0

namespace ns_stateMachine {

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
         * @brief E_STOP
         * @note
         * E_STOP conditions met/ physical e-stop triggered
         */
        E_STOP
    };

    class StateMachine
    {
        private:
            CAR_STATES              carState;     
            CAR_STOP_CONDITIONS     carStopReason;
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

            void getCarStatusCode(uint8_t*);
    };

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
            CommsListener(StateMachine*);
            CommsListener();

            void taskHeartbeatCheck(systemComms_t*, CAR_STOP_CONDITIONS);
            void taskImplausiblyCheck(systemComms_t*, systemComms_t*, CAR_STOP_CONDITIONS);

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

#endif /* !STATEMACHINE_H_ */
