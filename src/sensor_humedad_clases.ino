#include "SensorHumedadManager.h"
#include "../../../.platformio/packages/toolchain-atmelavr/avr/include/avr/io.h"
#include "../../../.platformio/packages/framework-arduinoavr/cores/arduino/HardwareSerial.h"
#include <SimpleTimer.h>

SimpleTimer timerEspera;
SensorHumedadManager manager;

int average = 0;
int MIN_MOISTURE = 20;
long SEGUNDO = 1000;
long MINUTO = SEGUNDO * 60;
long HORA = MINUTO * 60;
int muestras = 0;
int timerEsperaId;
int bombaPin = 7;
static const int BOMBA_ON = 1;

/*!
 * Para usar JSON
 */
//#include <SoftwareSerial.h>
#include <SerialJson.h>
SerialJson serialJson;
void core();


void setup()
{
    pinMode(bombaPin, INPUT);
    Serial.begin(115200);
    Serial.println("Reading from the sensor...");
    timerEsperaId = timerEspera.setInterval(HORA*6, idle);
//  delay(20000);
//  sense();
}

void sense()
{
    long time = 0;
    int av;
    average = 0;
    muestras = 0;
    while (muestras < 10)
    {
        if (millis() % SEGUNDO == 0)
        {
            //Serial.println("Sensando");
            av = manager.doSensing();
            average += av;
            muestras++;
        }
    }
    Serial.print("Final: ");
    Serial.println(average / 10);
    Serial.print("Bomba: ");
    Serial.println(digitalRead(bombaPin));
}

void idle()
{
    Serial.println("Iniciando");
    sense();
}

void loop()
{
    timerEspera.run();
    serialJson.check();
}

/*!
 * Funciones para el Leer el JSON
 */

void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        serialJson.inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '}') {
            serialJson.stringComplete = true;
        }
    }
}

void core(uint8_t tipo, uint32_t valor)
{
    if (tipo == 1) {  /// relevador
//    if (valor == 0) {
//      relay.off();
//    } else {
//      relay.on();
//    }
    }
    else if (tipo == 2) { /// bomba
//        bomba.velocity(valor);
    }
    else if (tipo == 3) {
//    if (valor == 0) {
//      aSwitch.off();
//    } else {
//      aSwitch.on();
//    }
    }
    else if (tipo == 4) {  /// timer
        // mandar llamar sense
    }
    else if (tipo == 5) { /// sensores de humedad

    }
}