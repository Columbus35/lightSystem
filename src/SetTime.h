#pragma once
#include "time.h"
#include <Arduino.h>
#include "FirebaseHandler.h"

class SetTimer{
public:
   void timer();
private:
 int previousIndex = 0;
 void setClock();
 void setLight(float onOff);
 void checkTime(int hour);

};