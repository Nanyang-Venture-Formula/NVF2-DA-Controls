/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_R2D
*/

/**
 * @brief
 * R2D criteria 
 * complete pre charge 
 * brake and start button engage simultaneously 
*/

#include <Arduino.h>

const uint8_t BrakeSwitch = 2;
const uint8_t ControlSwitch = 3;
const uint8_t BrakeLight = 4;
const uint8_t DashLight = 5;
const uint8_t Throttle  = 6; //indicate that Throttle on
const uint8_t Buzzer = 7;

void setup() {
  pinMode(BrakeSwitch, INPUT);
  pinMode(ControlSwitch, INPUT);
  pinMode(BrakeLight, OUTPUT);
  pinMode(DashLight, OUTPUT);
  pinMode(Throttle, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  //before R2D initated
  int BrakeState = digitalRead(BrakeSwitch);
  int ControlState = digitalRead(ControlSwitch);
  if(BrakeState == HIGH){
    //when the brake is press
    digitalWrite(BrakeLight, LOW);
    if (ControlState == HIGH){
      digitalWrite(DashLight, LOW);

    }
  }
  else{
    digtalWrite(BrakeLight, HIGH);
  }
}

