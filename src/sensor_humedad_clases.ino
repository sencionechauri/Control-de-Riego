#include "SensorHumedadManager.h"
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

void setup()
{
  pinMode(bombaPin, INPUT);
  Serial.begin(9600);
  Serial.println("Reading from the sensor...");
  timerEsperaId = timerEspera.setInterval(HORA*6, idle);
  delay(20000);
  sense();
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
}
