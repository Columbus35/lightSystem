#pragma once
#include "SetTime.h"
#include "NightLight.h"
#include "TempSensor.h"
#include "FirebaseHandler.h"
#define BULB_PIN 19

class LoopController{
    private:
     SetTimer setTimer;
     NightLight nightLight;
     TempSensor tempSensor;

    public:
     void loop(){
         bool bulbON;
         setTimer.timer();
         nightLight.checkDoor();
         tempSensor.tempBegin();
         if (FirebaseHandler::instance) {
         bulbON = FirebaseHandler::instance->getLightOn();
    }
    Firebase.ready();
    delay(100);
      (bulbON) ? digitalWrite(BULB_PIN, LOW) : digitalWrite(BULB_PIN, HIGH);
     }
};

 
