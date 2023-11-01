/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_R2D
*/

/**
 * @brief
 * R2D criteria->complete pre charge, brake and start button engage simultaneously 
 * R2D trigger -> change Carstate to R2D after being STOP/STOPPED
 * R2D to do -> trigger buzzer 
*/

#include <Arduino.h>
#include "NVF2/stateMachine.h"
#include "NVF2/throttleInterlock.h"
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"
#include "NVF2/boardDef.h"

#include <NVF2-Can/CanBus/NVF_Can.h>

StateMachine stateMachine;
CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;

MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_Can NVFCan0(&NVFCanI0, CommsDef::R2D_CAN_ID);
can_frame txBuf0;

void setup() {
  NVFCan0.setup();

  pinMode(BoardDef::PIN_R2D_PIN, INPUT);
  pinMode(BoardDef::PIN_ADC_1_0, INPUT);
  pinMode(BoardDef::PIN_BUZ_PIN, OUTPUT);
}

void loop() {
  //before R2D initated
  int BrakeState = digitalRead(BoardDef::PIN_R2D_PIN);
  int ControlState = digitalRead(BoardDef::PIN_ADC_1_0);
  if(BrakeState == 1 && ControlState == 1){
    //when the brake is press and the button is on
    txBuf0.data[0] = (uint8_t) 0xEE; 
  }
  else{
    txBuf0.data[0] = (uint8_t) 0; 
  }
}

