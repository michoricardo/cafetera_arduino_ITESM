
// TRIG al pin D12 ECHO al pin D13


#include <Servo.h> 
#define PIN_TRIG 12
#define PIN_ECO  13

Servo servo1; // se define el input para medir la flexion del sensor

const int echopin= 13;


void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600); 
  servo1.attach (9); 
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
}

void loop() {
  long duracion, distancia;  // Variables
  
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente
  int echosenal; // valor input del echo
  int servoposition; // valor de salida del servo
  echosenal= digitalRead(echopin);
  servoposition = map(echosenal, 727,960, 0, 180);
  servoposition = constrain(servoposition, 0, 120);
  

  
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;

/* Imprimir resultados a la terminal serial */
  if (distancia >= 500 || distancia <= 0){
    Serial.println("Fuera de rango");
  }
  else {
    Serial.print(distancia);
    Serial.println(" cm");
  }
  
  if (distancia >= 6
  serial. println ("Llenando");
  
  
  // Retardo para disminuir la frecuencia de las lecturas
  delay(500);  
}

