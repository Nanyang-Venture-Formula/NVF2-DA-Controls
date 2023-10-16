/**
 * @file main_passthru.cpp
 * @author Scott CJX
 * @brief WIP
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "CanFD/NVF_Can.h"

#define CAN_CSN1             10
#define CAN_CSN2             9
#define DELAY_MS            250

// CAN Network 1
MCP_CAN NVFCanI0(CAN_CSN1);
NVF_Can NVFCan0(&NVFCanI0, 0x01);

// CAN Network 2
MCP_CAN NVFCanI1(CAN_CSN2);
NVF_Can NVFCan1(&NVFCanI1, 0x01);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
  NVFCan1.setup();
}

can_frame rx_buf0;
can_frame rx_buf1;

void loop()
{
  if (NVFCan0.taskLoopRecv(&rx_buf0))
  {
    NVFCan1.tx(&rx_buf0);
  }

  if (NVFCan1.taskLoopRecv(&rx_buf1))
  {
    NVFCan0.tx(&rx_buf1);
  }
}