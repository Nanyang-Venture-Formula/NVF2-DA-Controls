/**
 * @file main_tx.cpp
 * @author SCOTT CJX
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
#define DELAY_MS            250

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x0F);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
}

uint8_t counter_buf = 0;

can_frame tx_buf;
void loop()
{
  if (counter_buf == -2) counter_buf = 0;

  tx_buf.data[0] = 0x00 + counter_buf;
  tx_buf.data[1] = 0xFF - counter_buf;

  tx_buf.can_dlc = 2;
  NVFCan0.tx(&tx_buf);
  delay(DELAY_MS);   // send data per 100ms
}