#include <Wire.h>           // Librería para la comunicación I2C
#include <Adafruit_INA219.h> // Librería para el sensor INA219
#include <driver/rtc_io.h>   // Librería para manejar el RTC

Adafruit_INA219 ina219;
float Current = 0.0;         // Variable para almacenar el valor de la corriente
const int mosfet_pin_high = 25;  // Pin GPIO para controlar el MOSFET en modo activo
const int mosfet_pin_low = 26;   // Pin GPIO para controlar el MOSFET en modo sueño profundo

// Tiempo de sueño en microsegundos (10 segundos)
const uint64_t SLEEP_DURATION_US = 10 * 1000000;

void setup() {
  Serial.begin(115200);    
  Wire.begin();               
  // Configura los pines de control de los MOSFETs
  pinMode(mosfet_pin_high, OUTPUT);
  pinMode(mosfet_pin_low, OUTPUT);
  // Inicializa el sensor INA219
  if (!ina219.begin()) {
    Serial.println("Error al inicializar INA219. Verifica las conexiones.");
    while (1);  // Detener ejecución si el INA219 no se inicializa
  }
  Serial.println("INA219 inicializado correctamente.");
  // Modo activo Inicio
  configureActiveMode();
}

void loop() {
  // Mide la corriente en el modo activo
  Current = ina219.getCurrent_mA();
  Serial.print("Corriente medida en modo activo: ");
  Serial.print(Current);
  Serial.println(" mA");
  // Simulación del proceso: Entra en modo de sueño profundo
  prepareDeepSleep();
  // Entrando en sueño profundo por 10 segundos
  esp_deep_sleep(SLEEP_DURATION_US);
}

// Esta función se ejecuta automáticamente después de que el ESP32 despierte del sueño profundo
void configureActiveMode() {
  // Configura los MOSFETs para seleccionar la resistencia shunt de bajo valor (modo activo)
  digitalWrite(mosfet_pin_high, HIGH);  // Activa el MOSFET de modo activo
  digitalWrite(mosfet_pin_low, LOW);    // Desactiva el MOSFET de modo bajo consumo
  delay(10);  // Tiempo de espera para estabilización
  // Mide la corriente al despertar (modo sueño profundo)
  Current = ina219.getCurrent_mA();
  Serial.print("Corriente medida en modo sueño profundo (despertar): ");
  Serial.print(Current);
  Serial.println(" mA");
}

void prepareDeepSleep() {
  // Configura los MOSFETs para seleccionar la resistencia shunt de alto valor (modo sueño profundo)
  digitalWrite(mosfet_pin_high, LOW);  // Desactiva el MOSFET de modo activo
  digitalWrite(mosfet_pin_low, HIGH);  // Activa el MOSFET de modo bajo consumo
  delay(10);  // Tiempo de espera para estabilización

}

