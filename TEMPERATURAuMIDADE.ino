// Aluno: Giuseppe Silva Favato
// RA: 417995
// Engenharia da computação 4° Ano - Noturno - Uningá
//Monitor de umidade do solo e temperatura ambiente para agricultores

#include <dht.h>

dht DHT;

#define DHT11_PIN 2
#define LDR_PIN A0

int valorldr = 0;
bool sensorReadLight = false;
bool sensorReadDark = false;
bool isLight = false;
const int pinoSensorUmidade = A1;
bool sensorReadMoisture = false;

void setup()
{
  pinMode(LDR_PIN, INPUT);
  Serial.begin(9600);
  pinMode(pinoSensorUmidade, INPUT);
  Serial.println("DHT TEST PROGRAM");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  valorldr = analogRead(LDR_PIN);

  if (valorldr > 1 && !isLight) {
    sensorReadLight = false;
    isLight = true;
  }

  if (valorldr == 0 && isLight) {
    sensorReadDark = false;
    isLight = false;
  }

  if (isLight && !sensorReadLight) {
    loopDHT();
    delay(2000);
    sensorReadLight = true;
  }

  if (!isLight && !sensorReadDark) {
    loopDHT();
    delay(2000);
    sensorReadDark = true;
  }

  if (valorldr == 0 && !sensorReadMoisture) {
    sensorReadMoisture = true;
  }
}

void loopDHT()
{
  int chk = DHT.read11(DHT11_PIN);

  Serial.print("DHT11,\t");
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);
  Serial.println("Sensor de Umidade do Solo: ");
  Serial.println(analogRead(pinoSensorUmidade));

  int umidadeSolo = analogRead(pinoSensorUmidade); 

  if (umidadeSolo > 600) {
    Serial.println(" ");
    Serial.println("PRECISA REGAR AS PLANTAS AGORA"); 
  }
  else{
    Serial.println(" ");
    Serial.println("Não é necessário regar as plantas agora! Pode regar no próximo horario recomendado: Às 07:00 horas ou às 19:00 horas");
  }

}
