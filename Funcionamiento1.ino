#include <esp_sleep.h>//Librería para control de sueño profundo

const int ledPin = 2;//LED interno de la ESP32


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  randomSeed(esp_random());//Inicializar la semilla aleatoria
  //Función que maneja el modo activo (operaciones aleatorias)
  modoActivoAleatorio();
  //Despertar después de 10 segundos en sueño profundo
  esp_sleep_enable_timer_wakeup(10000000);
  esp_deep_sleep_start();//Entra en sueño profundo
}
//Función para realizar operaciones matemáticas al azar
void operacionesMatematicasAleatorias() {
  int num1 = random(1, 100);  //Número aleatorio entre 1 y 100
  int num2 = random(1, 100);  //Número aleatorio entre 1 y 100
  int operacion = random(0, 4);  //Escoger una operación aleatoria

  switch (operacion) {
    case 0:
      Serial.print("Suma: ");
      Serial.println(num1 + num2); //Suma
      break;
    case 1:
      Serial.print("Resta: ");
      Serial.println(num1 - num2); //Resta
      break;
    case 2:
      Serial.print("Multiplicación: ");
      Serial.println(num1 * num2); //Multiplicación
      break;
    case 3:
      if (num2 != 0) { // Verificar que no sea división por 0
        Serial.print("División: ");
        Serial.println((float)num1 / num2); // División, ahora como flotante
      } else {
        Serial.println("División: No se puede dividir por 0");
      }
      break;
  }
}
//Función que simula operaciones aleatorias y comportamiento del LED en modo activo
void modoActivoAleatorio() {
  // Seleccionamos aleatoriamente un tipo de operación a realizar
  int operacion = random(1, 4);//Generar un número aleatorio entre 1 y 3
  switch (operacion) {
    case 1:
      //Operación 1:Parpadeo rápido del LED (solo un núcleo activo)
      Serial.println("Operación 1: Parpadeo rápido del LED");
      parpadearRapido(10);//Parpadear rápido 10 veces
      break;

    case 2:
      //Operación 2:Parpadeo lento del LED (solo un núcleo activo)
      Serial.println("Operación 2: Parpadeo lento del LED");
      parpadearLento(5);//Parpadear lentamente 5 veces
      break;

    case 3:
      //Operación 3:Encender el LED de manera fija por tiempo aleatorio (puede activar uno o dos núcleos)
      Serial.println("Operación 3: Encendido fijo del LED");
      encenderLedFijo();//Encender el LED durante un tiempo aleatorio
      break;

    default:
      Serial.println("Operación desconocida");
      break;
  }
  //Apagamos el LED antes de entrar en sueño profundo
  digitalWrite(ledPin, LOW);
}

// Función para parpadear el LED rápidamente
void parpadearRapido(int veces) {
  for (int i = 0; i < veces; i++) {
    digitalWrite(ledPin, HIGH);  // Encender el LED
    delay(100);  // Pausa de 100 ms
    digitalWrite(ledPin, LOW);   // Apagar el LED
    delay(100);  // Pausa de 100 ms
  }
}

// Función para parpadear el LED lentamente
void parpadearLento(int veces) {
  for (int i = 0; i < veces; i++) {
    digitalWrite(ledPin, HIGH);  // Encender el LED
    delay(500);  // Pausa de 500 ms
    digitalWrite(ledPin, LOW);   // Apagar el LED
    delay(500);  // Pausa de 500 ms
  }
}

// Función para encender el LED de manera fija por un tiempo aleatorio
void encenderLedFijo() {
  digitalWrite(ledPin, HIGH);  // Encender el LED

  // Tiempo aleatorio entre 1 y 5 segundos
  int tiempoEncendido = random(1000, 5000);
  delay(tiempoEncendido);  // Mantener el LED encendido durante el tiempo aleatorio
  digitalWrite(ledPin, LOW);  // Apagar el LED
}
