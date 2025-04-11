
#ifndef NIGHTLIGHT_H
#define NIGHTLIGHT_H
#include <Arduino.h>
#include "FirebaseHandler.h"
#define LIGHT_PIN 32
#define NIGHT_LED1 25
#define NIGHT_LED2 26
#define NIGHT_LED3 27

class NightLight{
    public:
    void checkDoor();

    private:
    long interval;
    int timer;
    bool doorWasClosed = false;
    bool openDoor = false;
    bool setInterval = false;
    bool checkInterval = true;
    bool cronometerStop= false;
    void doorIsOppen(bool sensor);
    void startLight();
    void cronometer();
};
#endif
