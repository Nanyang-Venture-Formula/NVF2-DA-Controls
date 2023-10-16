/**
 * @file main_tx_analog.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "CanFD/NVF_Can.h"

#define ANALOG_PIN          A0
#define CAN_CSN             10
#define DELAY_MS            250

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x0F);
can_frame tx_buf;

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
  pinMode(ANALOG_PIN, INPUT);
}

void loop()
{
  uint16_t reading = analogRead(ANALOG_PIN);
  tx_buf.data[0] = (uint8_t) reading;
  tx_buf.can_dlc = 1;

  //Serial Monitor
  Serial.print("Analog Reading: ");
  Serial.println(reading);

  if (NVFCan0.tx(&tx_buf))
  {
    Serial.println("CAN message sent successfully");
  }
  else
  {
    Serial.println("Error sending CAN message");
  }

  delay(DELAY_MS);   // send data per 100ms
}
