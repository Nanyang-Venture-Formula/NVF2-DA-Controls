/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** comms_definitions
*/

#ifndef COMMS_DEF_H_
#define COMMS_DEF_H_

#include "mcp_can.h"
#include "stdint.h"

namespace CommsDef
{
    const uint8_t CAN_SPEED = CAN_500KBPS;

    const uint32_t THROTTLEINTERLOCK1_CAN_ID = 0x0001;
    const uint32_t THROTTLEINTERLOCK2_CAN_ID = 0x0002;
    const uint32_t DATACOLLECTOR1_CAN_ID = 0x0003;
    const uint32_t DATACOLLECTOR2_CAN_ID = 0x0004;

    const uint32_t APPS1_CAN_ID = 0x0010;
    const uint32_t BPPC1_CAN_ID = 0x0011;

    const uint32_t APPS2_CAN_ID = 0x0012;
    const uint32_t BPPC2_CAN_ID = 0x0013;
}

#endif /* !COMMS_DEF_H_ */
