#include "time.h"
#include <Arduino.h>
#include "SetTime.h"
#include "FirebaseHandler.h"

SetTimer setTimer;

void SetTimer::timer(){
    setClock();
   }

void SetTimer::setClock(){
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    int hour = timeinfo.tm_hour;
    checkTime(hour);
}

void SetTimer::checkTime(int hour){
    int index1;
    int index2;
    if(FirebaseHandler::instance){
    index1 = FirebaseHandler::instance->getLightStart();
    index2 = FirebaseHandler::instance->getLightEnd();
    }
    
    if (index1 == hour && previousIndex == index1 - 1) {
        setLight(1);
        previousIndex = hour;
    } else if (index2 == hour && previousIndex == index2 - 1) {
        setLight(0);
        previousIndex = hour;
    } else {
        previousIndex = hour;
    }    
}

void SetTimer::setLight(float onOff){
      firebaseHandler.sendToFirebase(onOff, 3);
}