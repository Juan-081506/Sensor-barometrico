#define N 30 // número de lecturas en 5 minutos (10 segundos cada lectura)
float presiones[N];
int indice = 0;
bool lleno = false;

unsigned long ultimoTiempo = 0;
const unsigned long intervalo = 10000; // 10 segundos en ms

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("Error: no se detecto el sensor BMP280!");
    while (1);
  }
  Serial.println("Sensor BMP280 detectado.");
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimoTiempo >= intervalo) {
    ultimoTiempo = ahora;

    float presion_hPa = bmp.readPressure() / 100.0F;

    presiones[indice] = presion_hPa;
    indice++;
    if (indice >= N) {
      indice = 0;
      lleno = true;
    }

    Serial.print("Presion actual: ");
    Serial.print(presion_hPa);
    Serial.println(" hPa");

    if (lleno) {
      int indiceHace5Min = indice; // posición 5 minutos atrás en arreglo circular
      float presionHace5Min = presiones[indiceHace5Min];

      float cambio = presion_hPa - presionHace5Min;

      Serial.print("Cambio de presion en los ultimos 5 minutos: ");
      Serial.print(cambio);
      Serial.println(" hPa");

      float probLluvia = 0;
      if (cambio < 0) {
        probLluvia = min(-cambio * 30.0, 100.0);
      }

      Serial.print("Probabilidad estimada de lluvia: ");
      Serial.print(probLluvia);
      Serial.println(" %");
    } else {
      Serial.println("Recopilando datos para 5 minutos...");
    }

    Serial.println("------------------------");
  }
}





