#ifndef SensorHumedadManager_H
#define SensorHumedadManager_H

#include "Arduino.h"
#include "SensorHumedad.h"

class SensorHumedadManager
{
  public:
    SensorHumedadManager();
    int doSensing();
    int getAverage();

  private:
    SensorHumedad* sensors[];
    int average;
};

#endif
