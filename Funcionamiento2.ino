#include <Wire.h>
#include <Adafruit_INA219.h>

const int transistorActivePin = 18;//Transistor en modo activo
const int transistorSleepPin = 19;//Transistor en modo de sueño profundo
Adafruit_INA219 ina219;

void setup() {
  Serial.begin(115200); // Inicializar la comunicación serial
  Wire.begin();        // Iniciar el bus I2C

  pinMode(transistorActivePin, OUTPUT);
  pinMode(transistorSleepPin, OUTPUT);
}

void loop() {
  float current_mA = ina219.getCurrent_mA(); // Leer la corriente del ESP32-1 utilizando el sensor INA219
  Serial.print("Corriente medida: ");
  Serial.print(current_mA);
  Serial.println(" mA")

  // Controlar los transistores automáticamente según el valor de la corriente
  automaticTransistorControl(current_mA);
  // Esperar 1 segundo antes de realizar la siguiente medición
  delay(1000);
}

void automaticTransistorControl(float current) // Función para el control automático de los transistores basado en la corriente
{ 
  // Si la corriente es mayor a 1 mA (modo activo), encender el transistor de modo activo
  // Si la corriente es menor a 1 mA (modo de sueño profundo), encender el transistor de modo de sueño profundo
  digitalWrite(transistorActivePin, current > 1 ? HIGH : LOW); // Transistor para modo activo
  digitalWrite(transistorSleepPin, current <= 1 ? HIGH : LOW);  // Transistor para modo de sueño profundo
}
}
