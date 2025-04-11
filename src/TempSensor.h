#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "FirebaseHandler.h"
#define DHTPIN 22      
#define DHTTYPE DHT11  

class TempSensor{
    public:
    void tempBegin();


    private:
    long interval2;
    bool measure = true;
    bool startTimer = false;
    bool checkTimer = false;
    int timer2 = 10000;
    float temp;
    float hum; 
    void checkTemp();
    void runTimer();
};

#endif 