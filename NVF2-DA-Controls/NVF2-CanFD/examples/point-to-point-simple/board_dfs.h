/**
 * @file board_dfs.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>

namespace BoardDef
{
    const uint8_t CAN_CSN = 10;
};

namespace CommsDef
{
    namespace CanID
    {
        const unsigned long TX = 0x0F;
        const unsigned long RX = 0xFF;
    };
};
