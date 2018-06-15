//
// Created by Michel on 24/03/18.
//

#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch {
    int8_t _pin;

public:
    /*!
     *
     * @param pin - Digital PIN to controll switch on/off
     */
    Switch(int8_t pin) {
        _pin = pin;
        pinMode(_pin, OUTPUT);
        off();
    }
/*!
 * Switch on
 */
    void on() {
        digitalWrite(_pin, HIGH);
    }

    /*!
     * Switch off
     */
     void off() {
        digitalWrite(_pin, LOW);
    }

};


#endif //SWITCH_H
