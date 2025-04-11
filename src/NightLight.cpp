#include <Arduino.h>
#include "FirebaseHandler.h"
#include "NightLight.h"
#include "time.h"


NightLight nightLight;

void NightLight::checkDoor(){
    int lightSensor = analogRead(LIGHT_PIN);
    bool sensor;
    (lightSensor > 1500) ? sensor = true : sensor = false;
    if (FirebaseHandler::instance){
        timer = FirebaseHandler::instance->getTimer();
    }
    doorIsOppen(sensor);
}

void NightLight::doorIsOppen(bool sensor){
    if(!sensor){
        openDoor = true;
    }
    else{
        openDoor = false;
        doorWasClosed = true;
    }
    startLight();
}

void NightLight::startLight(){
    if (FirebaseHandler::instance) {
        timer = FirebaseHandler::instance->getTimer();
    }
    if(openDoor && doorWasClosed){
        digitalWrite(NIGHT_LED1, HIGH);
        digitalWrite(NIGHT_LED2, HIGH);
        digitalWrite(NIGHT_LED3, HIGH);
        setInterval = true;
    }
    
    else{
        digitalWrite(NIGHT_LED1, LOW);
        digitalWrite(NIGHT_LED2, LOW);
        digitalWrite(NIGHT_LED3, LOW);

    }
     if(setInterval && checkInterval){
            interval = millis() + timer;
            setInterval = false;
            checkInterval = false;
            cronometerStop = true;
      }
      cronometer();
}

void NightLight::cronometer(){
   if(cronometerStop) {
   if (millis() < interval){
        checkInterval = false;
    }
    else{
        doorWasClosed = false;
        checkInterval = true;
        cronometerStop = false;
    }
   }
}


