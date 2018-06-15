#include "SensorHumedadManager.h"

SensorHumedadManager::SensorHumedadManager()
{
  sensors[0] = new SensorHumedad(A0);
  sensors[1] = new SensorHumedad(A1);
  sensors[2] = new SensorHumedad(A2);
  sensors[3] = new SensorHumedad(A3);
}

int SensorHumedadManager::doSensing()
{
  average = 0;
  for (int i = 0; i < 4; i++)
  {
    average += sensors[i]->getValue();
  }
  average = average / 4;
  return average;
}

int SensorHumedadManager::getAverage()
{
  return average;
}
