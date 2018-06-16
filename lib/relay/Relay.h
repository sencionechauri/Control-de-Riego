#ifndef Relay_H
#define Relay_H

#include "Arduino.h"

class Relay
{
    int pin_relevador;

public:
    Relay(int pin)
    {
        pin_relevador = pin;
        pinMode(pin_relevador, OUTPUT);
    }
    void on()
    {
        digitalWrite(pin_relevador, HIGH);
    }
    void off()
    {
        digitalWrite(pin_relevador, LOW);
    }
};

#endif
