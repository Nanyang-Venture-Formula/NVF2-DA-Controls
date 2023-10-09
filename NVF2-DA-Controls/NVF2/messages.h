/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** messages
*/

#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "stdint.h"

struct apps_s
{
    uint64_t raw_reading;
    uint32_t mapped_reading;
    bool is_calibrating;
};

#endif /* !MESSAGES_H_ */
