/**
 * @file NVF_Can.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 12-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef NVF_CAN_H_
#define NVF_CAN_H_

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <stdint.h>

#define ul unsigned long

struct can_frame
{
  unsigned long can_id = 0xFF;
  uint8_t can_dlc;
  uint8_t data[8];
};

class NVF_Can
{
private:
  ul thisCanID;
  MCP_CAN *CAN;

public:
  NVF_Can(MCP_CAN *CAN, ul canId);
  bool setup();
  bool tx(can_frame *);
  bool taskLoopRecv(can_frame *);
};

#endif /* !NVF_CAN_H_ */