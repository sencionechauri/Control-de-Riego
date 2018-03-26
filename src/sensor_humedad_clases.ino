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
long delayOriginal = 2;
int contador = 0;

void setDelayReading(long minutos)
{
  timerEspera.disable(timerEsperaId);
  timerEsperaId = timerEspera.setInterval(MINUTO * minutos, idle);
  timerEspera.enable(timerEsperaId);
}

void setup()
{
  pinMode(bombaPin, INPUT);
  Serial.begin(9600);
  Serial.println("Reading from the sensor...");
  timerEsperaId = timerEspera.setInterval(MINUTO*2, idle);
  delay(10000);
  sense();
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
  contador++;
  if (contador == 3)
  {
    Serial.println("Modificar");
    setDelayReading(1);
  }
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
