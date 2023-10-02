/*
** EPITECH PROJECT, 2023
** NVF2-DA-Controls
** File description:
** comms_definitions
*/

#ifndef COMMS_DEF_H_
#define COMMS_DEF_H_

#include "stdint.h"

namespace CommsDef
{
    const uint32_t THROTTLEINTERLOCK_CAN_ID = 0xFFD1;
    const uint32_t DATACOLLECTOR_CAN_ID = 0xFFD2;

    const uint32_t APPS1_CAN_ID = 0xFFA1;
    const uint32_t APPS2_CAN_ID = 0xFFA2;

    const uint32_t BPPC1_CAN_ID = 0xFFB1;
    const uint32_t BPPC2_CAN_ID = 0xFFB2;
}

#endif /* !COMMS_DEF_H_ */
