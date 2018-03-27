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
long delayOriginal = 2;
int contador = 0;

void setDelayReading(long minutos)
{
  timerEspera.disable(timerEsperaId);
  timerEsperaId = timerEspera.setInterval(MINUTO * minutos, idle);
  timerEspera.enable(timerEsperaId);
}

/*!
 * Para usar JSON
 */
//#include <SoftwareSerial.h>
#include <SerialJson.h>
SerialJson serialJson;
void core();

/*!
 * Para usar el relevador
 */

#include <Relay.h>
Relay relay(2);

/*!
 * Para usar el transistor (switch)
 */
#include <Switch.h>
Switch aSwitch(8);

void setup()
{

  pinMode(bombaPin, INPUT);
    Serial.begin(9600);
  Serial.println("Reading from the sensor...");
//  timerEsperaId = timerEspera.setInterval(MINUTO*2, idle);
//  delay(10000);
//  sense();
}

void sense(){
  int av;
  average = 0;
  muestras = 0;
  long t = millis();
  while (muestras < 10)
  {
    if ((millis() - t) >= SEGUNDO)
    {
      t = millis();
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
  Serial.print("Contador: ");
  Serial.println(contador);
    if (average / 10 < 20)
    {
        relay.on();
    }
//  contador++;
//  if (contador == 3)
//  {
//    Serial.println("Modificar");
//    setDelayReading(1);
//  }

}

void idle()
{
    Serial.println("Iniciando");
    sense();
}

void loop()
{
//    timerEspera.run();
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
        if (valor == 0) {
            relay.off();
        } else {
            relay.on();
        }
    }
    else if (tipo == 2) { /// bomba
//        bomba.velocity(valor);
    }
    else if (tipo == 3) {
        if (valor == 0) {
            aSwitch.off();
        } else {
            aSwitch.on();
        }
    }
    else if (tipo == 4) {  /// timer
        Serial.println("Cambiando Timer");
        setDelayReading(valor);
    }
    else if (tipo == 5) { /// sensores de humedad
        sense();
    }
}