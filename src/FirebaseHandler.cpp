#include "FirebaseHandler.h"
#include <FirebaseESP32.h>
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"

FirebaseHandler firebaseHandler;
FirebaseHandler* FirebaseHandler::instance = nullptr;


FirebaseHandler* FirebaseHandler::getInstance() {
    if (!instance) {
        instance = new FirebaseHandler();
    }
    return instance;
}

bool FirebaseHandler::getLightOn() const {
    return lightOn;
}

long FirebaseHandler::getTimer() const {
    return timer;
}

int FirebaseHandler::getLightStart() const {
    return lightStart;
}

int FirebaseHandler::getLightEnd() const {
    return lightEnd;
}

int FirebaseHandler::getHumHouse() const {
    return humHouse;
}

int FirebaseHandler::getTempHouse() const {
    return tempHouse;
}



FirebaseData fbdoHandler; 

void FirebaseHandler::startConnection() {
    instance = this;
    initializeFirebase();
    Firebase.setStreamCallback(fbdoHandler, streamCallback, streamTimeoutCallback); // ⚠️ GEÄNDERT
}

void FirebaseHandler::initializeFirebase() {
    config.api_key = "Firebase api kez";
    config.database_url = "Firebase Url";

    auth.user.email = "acces email address";
    auth.user.password = "password";

    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    unsigned long startMillis = millis();
    while (!Firebase.ready()) {
        Serial.print(".");
        delay(500);
        if (millis() - startMillis > 10000) {
            Serial.println("\n❌ FEHLER: Token konnte nicht generiert werden!");
            return;
        }
    }

    Firebase.beginStream(fbdoHandler, "/");
    fetchInitialValues();
}

void FirebaseHandler::fetchInitialValues() {
    Serial.println("Fetching initial values from Firebase...");
    bool syncError = false;

    if (Firebase.getInt(fbdoHandler, "/lightOn")) { 
        lightOn = fbdoHandler.intData(); 
        Serial.print("Fetched lightOn: "); Serial.println(lightOn);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }

    if (Firebase.getInt(fbdoHandler, "/lightStart")) {
        lightStart = fbdoHandler.intData();
        Serial.print("Fetched lightStart: "); Serial.println(lightStart);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }

    if (Firebase.getInt(fbdoHandler, "/lightEnd")) {
        lightEnd = fbdoHandler.intData();
        Serial.print("Fetched lightEnd: "); Serial.println(lightEnd);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }

    if (Firebase.getInt(fbdoHandler, "/timer")) {
        timer = fbdoHandler.intData();
        Serial.print("Fetched timer: "); Serial.println(timer);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }

     if (Firebase.getInt(fbdoHandler, "/humHouse")) {
        humHouse = fbdoHandler.intData();
        Serial.print("Fetched timer: "); Serial.println(humHouse);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }

     if (Firebase.getInt(fbdoHandler, "/tempHouse")) {
        tempHouse = fbdoHandler.intData();
        Serial.print("Fetched timer: "); Serial.println(tempHouse);
    } else {
        Serial.println(fbdoHandler.errorReason());
        syncError = true;
    }
    if(syncError){fetchInitialValues();}
}

void FirebaseHandler::streamCallback(StreamData data) {
    if (instance) {
            String path = data.dataPath();
            if (path == "/lightOn") {
                instance->lightOn = data.intData();
                Serial.print("Updated lightOn: "); Serial.println(instance->lightOn);
            } else if (path == "/lightStart") {
                instance->lightStart = data.intData();
            } else if (path == "/lightEnd") {
                instance->lightEnd = data.intData();
            } else if (path == "/timer") {
                instance->timer = data.intData();
            }
            else if (path == "/humHouse") {
                instance->humHouse = data.intData();
            }
            else if (path == "/tempHouse") {
                instance->tempHouse = data.intData();
            }
            Serial.print("🔄 New value: ");
            Serial.println(data.intData());
        }
}

void FirebaseHandler::streamTimeoutCallback(bool timeout) {
    if (timeout) {
        Serial.println("🔥 Firebase stream timeout, retrying...");
        Firebase.beginStream(instance->fbdoHandler, "/"); 
    }
}

void FirebaseHandler::sendToFirebase(float value, int pos) {
    setTemp(value, pos);
}

void FirebaseHandler::setTemp(float value, int pos) {
    switch (pos)
    {
    case 1: 
        if (Firebase.setFloat(fbdoHandler, "/tempHouse", value)) { 
        Serial.print("✅ Successfully set: temp = ");
        Serial.println(value);
    } else {
        Serial.print("❌ Error setting lightOn: ");
        Serial.println(fbdoHandler.errorReason());
    }
        break;
    
    case 2:
        if (Firebase.setFloat(fbdoHandler, "/humHouse", value)) { 
        Serial.print("✅ Successfully set: hum = ");
        Serial.println(value);
    } else {
        Serial.print("❌ Error setting lightOn: ");
        Serial.println(fbdoHandler.errorReason());
    } 
        break;
    case 3:
        if (Firebase.setFloat(fbdoHandler, "/lightOn", value)) { 
        Serial.print("✅ Successfully set: lightOn = ");
        Serial.println(value);
    } else {
        Serial.print("❌ Error setting lightOn: ");
        Serial.println(fbdoHandler.errorReason());
    } 
        break;    
    }

}
