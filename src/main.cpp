#include <Arduino.h>
#include "SetupControler.h"
#include "FirebaseHandler.h"
#include "LoopControler.h"



SetupControler setupControler;
LoopController loopController;
int getStableADC();

void setup() {
   setupControler.setup();
}

void loop() {
    loopController.loop();
}

