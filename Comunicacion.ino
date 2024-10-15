#define BLYNK_PRINT Serial  
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YOUR_BLYNK_AUTH_TOKEN"; 
char ssid[] = "MillerCel";  
char pass[] = "123456789";     

float current = 0;

BlynkTimer timer;

void sendCurrentData() {
  Blynk.virtualWrite(V0, current);
}

void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(10000L, sendCurrentData); //temporizador para enviar datos cada 10 segundos
}

void loop() {
  Blynk.run();
  timer.run();
}
