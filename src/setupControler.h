#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "WiFiConnector.h"
#include "FirebaseHandler.h"
#define LIGHT_PIN 32
#define NIGHT_LED1 25
#define NIGHT_LED2 26
#define NIGHT_LED3 27
#define BULB_PIN 19

class SetupControler {
private:
    WiFiConnector wifiConnector; 
    FirebaseHandler firebaseHandler;
public:
    void setup() {
        Serial.begin(9600);
        pinMode(LIGHT_PIN, INPUT_PULLDOWN);
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(NIGHT_LED1, OUTPUT);
        pinMode(NIGHT_LED2, OUTPUT);
        pinMode(NIGHT_LED3, OUTPUT);
        pinMode(BULB_PIN, OUTPUT);
        digitalWrite(NIGHT_LED1, LOW);
        digitalWrite(NIGHT_LED2, LOW);
        digitalWrite(NIGHT_LED3, LOW);
        digitalWrite(BULB_PIN, HIGH);
        wifiConnector.connect(); 
        firebaseHandler.startConnection();
    }
};
#endif 