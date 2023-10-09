/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_APPS
*/

#include <Arduino.h>
#include "NVF2/commsDef.h"
#include "NVF2/commsHandler.h"
#include "NVF2/boardDef.h"
#include "NVF2/hardwareHandler.h"

const uint16_t APPS_1_PIN = A0; //pin of APPS 1 
const uint16_t APPS_2_PIN = A1; //pin of APPS 2 

const unsigned long calibration_period = 10000;  // 10 seconds
const unsigned long syncInterval = 1000; //1 second
const unsigned long appsCheckTime = 100; //100 millisecond   
int apps_time = 0; //time where plausibility starts 
bool apps_state = true;

CommsHandler commsHandler;
systemComms_t TIComms;
HardwareHandler apps1(APPS_1_PIN);
HardwareHandler apps2(APPS_2_PIN);

void setup()
{
    Serial.begin(115200);

    commsHandler = CommsHandler();
    commsHandler.begin();
    // todo make this dynamic
    commsHandler.CAN_begin(CommsDef::APPS1_CAN_ID, BoardDef::PIN_CANSPI_CSN);

    // define buffers for comms that i want to interact with
    TIComms = systemComms_t();
    TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;
}

void loop()
{
    /**
     * @todo
     * @pseudocode
     *
     * if calibrate mode
     * calibrate and sync with other APPS sensors
     */
    if (!apps1.isCalibrated() || !apps2.isCalibrated()){
        apps1.calibrate();
        apps2.calibrate();
    }
    apps1.sync();
    apps2.sync();  
    // recieve CAN buffer
    commsHandler.CAN_RX();

    /**
     * @todo
     * @pseudocode
     *
     * hardwarehandler.getSensorValue()
     * hardwarehandler.getMappedSensorValue()
     * send sensor value
     */

    int sensor1Value = apps1.readValue();
    int sensor2Value = apps2.readValue();
    int avg = (sensor1Value + sensor2Value)/2; 
    int score1 = sensor1Value - avg;
    int score2 = avg - sensor2Value; //BOTH should be the inverse of one another 
    int maxvalid = score1 * 1.1;
    int minvalid = score1 * 0.9; 
    /**
     * T11.8.9 plausbility check 
     * deviation > 10% any used APPS   
    */
    if (score2 > maxvalid || score2 < minvalid){
        if (apps_time == 0){
            apps_time = millis();
        }
        else if (apps_time - millis() > appsCheckTime){
            //implausibility lasts for more than 100ms 
            apps_time = 0; //reset to 0 
            apps_state = false; 
        }
    }
    /**
     * System Critical Signal Check 
     * short circuit to ground, short circuit to voltage supply 
    */
    if (sensor1Value == 5 && sensor2Value == 5){
        apps_state = false;
    }
    
    // todo send CAN tx to report stateMachine carState
    commsHandler.CAN_TX();
}
