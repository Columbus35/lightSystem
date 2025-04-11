#ifndef FIREBASEHANDLER_H
#define FIREBASEHANDLER_H

#include <FirebaseESP32.h>

class FirebaseHandler {
public:
    static FirebaseHandler* instance;
    static FirebaseHandler* getInstance();
    void startConnection();
    void sendToFirebase(float value, int pos);
    bool getLightOn() const;
    long getTimer() const;
    int getLightStart() const;
    int getLightEnd() const;
    int getTempHouse() const;
    int getHumHouse() const;

private:
    int lightEnd = 0;
    int lightStart = 0;
    bool lightOn = 0;
    long timer = 0;
    int humHouse = 0;
    int tempHouse = 0;
    FirebaseAuth auth;
    FirebaseConfig config;
    FirebaseData fbdoHandler;
    

    void initializeFirebase();
    void fetchInitialValues();
    static void streamCallback(StreamData data);
    static void streamTimeoutCallback(bool timeout);
    void setTemp(float value, int pos);
};

extern FirebaseHandler firebaseHandler;
#endif 