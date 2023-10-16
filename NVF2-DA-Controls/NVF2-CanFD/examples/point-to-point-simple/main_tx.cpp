/**
 * @file main_tx.cpp
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

#define DELAY_MS            250

MCP_CAN NVFCanI(BoardDef::CAN_CSN);
NVF_Can NVFCan(&NVFCanI, CommsDef::CanID::TX);

uint8_t counter_buf = 0;
can_frame tx_buf;

void setup()
{
  Serial.begin(115200);
  NVFCan.setup();
}

void loop()
{
  if (counter_buf == -1) counter_buf = 0;

  tx_buf.data[0] = 0x00 + counter_buf;
  tx_buf.data[1] = 0xFF - counter_buf;

  tx_buf.can_dlc = 2;
  NVFCan.tx(&tx_buf);

  delay(DELAY_MS);   // send data per 100ms
}