//
// Created by Michel on 26/03/18.
//

#ifndef CONTROL_DE_RIEGO_SERIALJSON_H
#define CONTROL_DE_RIEGO_SERIALJSON_H

#include <Arduino.h>
#include <ArduinoJson.h>

class SerialJson {
    StaticJsonBuffer<512> jsonBuffer;

public:
    String inputString = "";         // a string to hold incoming data
    boolean stringComplete = false;  // whether the string is complete
    SerialJson() {}

    void check() {
        if (stringComplete) {
            // Serial.println(inputString);
            // Serial.println(inputString.length());
            JsonObject& root = jsonBuffer.parse(inputString);
            // root.printTo(Serial);

            uint8_t tipo = root["tipo"];
            uint32_t valor = root["valor"];
            Serial.println(tipo);
            Serial.println(valor);
            jsonBuffer.clear();
            core(tipo, valor);
            // clear the string:
            inputString = "";
            stringComplete = false;
        }
    }

};


#endif //CONTROL_DE_RIEGO_SERIALJSON_H
