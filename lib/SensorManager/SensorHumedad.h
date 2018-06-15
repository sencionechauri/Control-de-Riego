#ifndef SensorHumedad_H
#define SensorHumedad_H

#include "Arduino.h"

class SensorHumedad
{
  public:
    SensorHumedad(int pinValue) : pin(pinValue) {}
    void setPin(int value);
    int getPin();
    int getValue();

  private:
    int pin;
    int value;
    static const int MIN_READING = 190;
    static const int MAX_READING = 1023;
};

#endif
