#include "DFRobot_HumanDetection.h"

DFRobot_HumanDetection hu(&Serial1);

void setup(){
    Serial.begin(115200);
    Serial1.begin(115200,SERIAL_8N1,4,5);
    while(hu.begin() != 0){
        Serial.println("init error!!!");
        delay(1000);
    }
    Serial.println("init success");
    //delay(100);
    while(hu.configWorkMode(hu.eSleepMode) != 0){
        Serial.println("init error!!!");
        delay(1000);
    }
    Serial.println("init success");
    Serial.println(hu.getWorkMode());
    //delay(100);
    //hu.configLEDLight(hu.eHPLed,0);
    Serial.println(hu.getLEDLightState(hu.eHPLed));
    Serial.println(hu.smHumanData(hu.eHumanDistance));
    Serial.println(hu.smHumanData(hu.eHumanMovingRange));
    Serial.println(hu.smHumanData(hu.eHumanMovement));
    Serial.println(hu.smHumanData(hu.eHumanPresence));
    int16_t x,y,z;
    hu.smHumanLocation(&x,&y,&z);
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
}



void loop(){

}