#include "TempSensor.h"
#include "DHT.h"

#define DHTPIN 22
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void TempSensor::tempBegin(){
     dht.begin();
     if(measure){checkTemp();
        measure = false;
        checkTimer = true;
    }
    if(checkTimer){
       interval2 = millis() + timer2;
       checkTimer = false;
       startTimer = true;
    }
    if(startTimer){runTimer();}
}

void TempSensor::runTimer(){
    if(millis() > interval2){
        measure = true;
        startTimer = false;
    }
}

void TempSensor::checkTemp() {
    if (FirebaseHandler::instance) {
        temp = FirebaseHandler::instance->getTempHouse();
        hum = FirebaseHandler::instance->getHumHouse();
    }

    float tempTempor = dht.readTemperature();
    float humTempor = dht.readHumidity();

    if (abs(tempTempor - temp) >= 0.4) {
        firebaseHandler.sendToFirebase(tempTempor, 1);
    }

    if (abs(humTempor - hum) >= 4.0) {
        firebaseHandler.sendToFirebase(humTempor, 2);
    }
}