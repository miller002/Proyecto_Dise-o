void setup() {
// Pin del LED interno
  pinMode(2, OUTPUT);  
  // MODO ACTIVO: Encendido LED interno
  digitalWrite(2, HIGH);  // Enciende el LED para generar corriente (alrededor de 50-100 mA)
  delay(10000); // Mantiene el modo activo por 10 segundos
  enterDeepSleep();
}

void loop() {
  // MODO SUEÑO PROFUNDO: Apagamos el ESP32
  digitalWrite(2, LOW);  // Apaga el LED
  esp_sleep_enable_timer_wakeup(10000000); //Despertar la ESP32 después de 10 segundos
  esp_deep_sleep_start();  // Inicia el modo de sueño profundo
}


