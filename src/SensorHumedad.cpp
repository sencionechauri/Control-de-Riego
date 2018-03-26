#include "SensorHumedad.h"

void SensorHumedad::setPin(int value)
{
  pin = value;
}

int SensorHumedad::getPin()
{
  return pin;
}

int SensorHumedad::getValue()
{
  value = analogRead(pin);
  value = map(value, MAX_READING, MIN_READING, 0, 100);
  return value;
}
