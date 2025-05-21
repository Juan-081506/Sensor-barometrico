/*
Proyecto: Medición de Presión Barométrica y Altitud con Arduino y BMP280

Asegurate de instalar las siguientes librerías antes de subir el código:

- Adafruit BMP280
- Adafruit Unified Sensor

Puedess instalarlas desde el Gestor de Librerías del IDE de Arduino:
1. Abrí el IDE de Arduino.
2. Ve a "Programa" > "Incluir Librería" > "Gestionar bibliotecas..."
3. Busca "Adafruit BMP280" e instalala.
4. Busca "Adafruit Unified Sensor" e instalala también.

Este código te permitirá leer la presión atmosférica (en hPa)
y calcular la altitud relativa con respecto al nivel del mar,
usando una presión de referencia estándar (1013.25 hPa).


¡Sientete libre de modificar el codigo!
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h> // Librería para el sensor BMP280

// Crear el objeto del sensor
Adafruit_BMP280 bmp; // Usamos comunicación I2C por defecto

void setup() {
Serial.begin(9600); // Iniciar la comunicación serial a 9600 baudios

// Inicializar el sensor BMP280
if (!bmp.begin(0x76)) { // La dirección puede ser 0x76 o 0x77 según el módulo
Serial.println("¡Error: no se detectó el sensor BMP280!");
while (1); // Detiene el programa si no se encuentra el sensor
}

Serial.println("Sensor BMP280 detectado y funcionando.");
}

void loop() {
// Leer la presión del sensor (en pascales) y convertir a hectopascales
float presion_hPa = bmp.readPressure() / 100.0F;

// Calcular la altitud estimada en metros
// El valor 1013.25 es la presión atmosférica estándar al nivel del mar en hPa
float altitud_metros = bmp.readAltitude(1013.25);

// Imprimir la presión en el monitor serial
Serial.print("Presión: ");
Serial.print(presion_hPa);
Serial.println(" hPa");

// Imprimir la altitud estimada
Serial.print("Altitud estimada: ");
Serial.print(altitud_metros);
Serial.println(" m");

Serial.println("-----------------------------");

delay(2000); // Esperar 2 segundos antes de la siguiente lectura
}
