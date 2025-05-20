Medición de Presión Barométrica con Arduino (BMP280)
Este proyecto utiliza un sensor barométrico BMP280 junto a un Arduino Uno para medir la presión atmosférica y estimar la altitud relativa. Sirve como herramienta para actividades como senderismo, monitoreo ambiental o estudios de clima.
Objetivos:
- Medir la presión atmosférica en tiempo real.
- Calcular la altitud relativa con base en la presión.
- Aplicar el sistema en entornos reales (clima, deporte, geografía).
Materiales necesarios
- Arduino Uno
- Sensor BMP280 (protocolo I2C) - Cables Dupont
- Protoboard
- PC con el IDE de Arduino
Conexiones del sensor (I2C)

| Pin del sensor | Pin en Arduino Uno | 
|----------------|--------------------|
| VCC            | 3.3V               |
| GND            | GND                |       
| SDA            | A4                 |
| SCL            | A5                 |

