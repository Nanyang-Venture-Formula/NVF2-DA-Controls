/**
 * @file main_rx.cpp
 * @author Scott CJX
 * @brief 
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "CanFD/NVF_Can.h"

#define CAN_CSN             10

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x01);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
}

can_frame rx_buf;

void loop()
{
  if (NVFCan0.taskLoopRecv(&rx_buf))
  {
      Serial.print(rx_buf.can_id, HEX);
      Serial.print(": ");
      Serial.print(rx_buf.can_dlc);
      Serial.print("->");

    for (int i = 0; i < rx_buf.can_dlc; i++)
    {
      Serial.print(rx_buf.data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}