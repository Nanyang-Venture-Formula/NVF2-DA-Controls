/**
 * @file NVF_Can.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 12-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "NVF_Can.h"

/**
 * @brief Construct a new nvf can::nvf can object
 * 
 * @param CAN 
 * @param canId 
 */
NVF_Can::NVF_Can(MCP_CAN *CAN, unsigned long canId)
{
  this->thisCanID = canId;
  this->CAN = CAN;
}

/**
 * @brief setup CAN Bus
 * 
 * @return true when setup ok
 */
bool NVF_Can::setup()
{
  SPI.begin();
  while (CAN_OK != this->CAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ))
  {
    Serial.println("CAN BUS initialisation failed");
    delay(500);
  }

  this->CAN->setMode(MCP_NORMAL);
  Serial.println("CAN BUS initialisation successful");
  return 1;
}

/**
 * @brief 
 * 
 * @param frame 
 * @return true if successful send
 */
bool NVF_Can::tx(can_frame *frame)
{
  uint8_t ret = this->CAN->sendMsgBuf(frame->can_id, frame->can_dlc, frame->data);
  return (ret == CAN_OK);
}

/**
 * @brief 
 * 
 * @param buf 
 * @return true when buf populated;
 * @return false if no message
 */
bool NVF_Can::taskLoopRecv(can_frame *buf)
{
  if (CAN_MSGAVAIL == this->CAN->checkReceive())
  {
    this->CAN->readMsgBuf(&buf->can_id, &buf->can_dlc, buf->data);

    Serial.print("ID: 0x");
    Serial.print(buf->can_id, HEX);
    return 1;
  }

  return 0;
}
