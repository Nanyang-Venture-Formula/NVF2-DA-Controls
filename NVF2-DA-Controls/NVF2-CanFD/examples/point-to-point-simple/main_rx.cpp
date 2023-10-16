/**
 * @file main_rx.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>

#include "board_dfs.h"
#include "CanFD/NVF_Can.h"

MCP_CAN NVFCanI(BoardDef::CAN_CSN);
NVF_Can NVFCan(&NVFCanI, CommsDef::CanID::TX);

void setup()
{
  Serial.begin(115200);
  NVFCan.setup();
}

can_frame rx_buf;

void loop()
{
  if (NVFCan.taskLoopRecv(&rx_buf))
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