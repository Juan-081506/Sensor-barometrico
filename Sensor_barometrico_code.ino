// Este código mide la presión atmosférica y calcula la altura sobre el nivel del mar
// También estima la probabilidad de lluvia basada en el cambio de presión
// Se toman lecturas cada 10 segundos durante 1 minuto

// Fórmula para el número de lecturas (N):
// N = Tiempo_total / intervalo_entre_lecturas
// Por ejemplo, para 1 minuto (60 segundos) y lecturas cada 10 segundos:
// N = 60 / 10 = 6
// Si quieres cambiar el tiempo total o el intervalo, ajusta ambos valores.

#define N 6 // número de lecturas en 1 minuto (10 segundos cada una)
float presiones[N];
int indice = 0;
bool lleno = false;

// Presión atmosférica al nivel del mar en tu ubicación (en hPa)
// Este valor debe ajustarse para una mayor precisión
const float PRESION_NIVEL_MAR = 1012.0;

unsigned long ultimoTiempo = 0;
const unsigned long intervalo = 10000; // intervalo entre lecturas (10 segundos)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("No se detectó en 0x76. Probando 0x77...");
    if (!bmp.begin(0x77)) {
      Serial.println("Error: no se detectó el sensor BMP280 en 0x76 ni 0x77!");
      while (1);
    }
  }

  Serial.println("Sensor BMP280 detectado.");
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimoTiempo >= intervalo) {
    ultimoTiempo = ahora;

    float presion_hPa = bmp.readPressure() / 100.0F;
    float altitud_nivel_mar = bmp.readAltitude(PRESION_NIVEL_MAR); // Altura sobre el nivel del mar

    presiones[indice] = presion_hPa;
    indice++;
    if (indice >= N) {
      indice = 0;
      lleno = true;
    }

    Serial.print("Presión actual: ");
    Serial.print(presion_hPa);
    Serial.println(" hPa");

    Serial.print("Altura sobre el nivel del mar: ");
    Serial.print(altitud_nivel_mar);
    Serial.println(" m");

    if (lleno) {
      int indiceHace1Min = indice;
      float presionHace1Min = presiones[indiceHace1Min];
      float cambio = presion_hPa - presionHace1Min;

      Serial.print("Cambio de presión en el último minuto: ");
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
      Serial.println("Recopilando datos para 1 minuto...");
    }

    Serial.println("------------------------");
  }
}



