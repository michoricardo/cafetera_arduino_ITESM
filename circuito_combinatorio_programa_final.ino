/* programa de circuito secuencial Ricardo García
*/

#include <Servo.h>
/*
 Sensor de Ultrasonico HC-SR04 con Arduino

Conexiones:
 - TRIG al pin D12
 - ECHO al pin D13
***/
#define PIN_TRIG 12
#define PIN_ECO  13
int entrada1=3;
int entrada2=4;
int salida=5;
int altobajo1=0;
int altobajo2=0;
int activabomba=8;
Servo miservo;
Servo miservo1;
void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600);  
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  pinMode(salida, OUTPUT);
  pinMode(activabomba,OUTPUT);
  miservo.attach(6);
  miservo1.attach(7);
}
void loop() {
  altobajo1=digitalRead(3);
  altobajo2=digitalRead(4);
  long duracion, distancia;  // Variables
  
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente
  
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;
  Serial.print(distancia);
   Serial.println("distancia en centimetros");
  if(altobajo1==HIGH && distancia >=13){
  digitalWrite(activabomba,HIGH);
   miservo.write(0);
   delay(1000);
   miservo.write(180);
   delay(1000);
   miservo.write(0);
   delay(3000);
  
  Serial.print(distancia);
   Serial.println("distancia en centimetroskkkk");
}

else{
  Serial.print(distancia);
   Serial.println("distancia en centimetrosllll");
   digitalWrite(activabomba,LOW);
  }
 if(altobajo2==HIGH && distancia >=13){
  digitalWrite(activabomba,HIGH);
   miservo1.write(0);
   delay(1000);
   miservo1.write(180);
   delay(1000);
   miservo1.write(0);
   delay(3000);
  
  Serial.print(distancia);
   Serial.println("distancia en centimetroskkkk");
}

else{
  Serial.print(distancia);
   Serial.println("distancia en centimetrosllll");
   digitalWrite(activabomba,LOW);
  }
if (distancia<=13){
  digitalWrite(salida,HIGH);
  digitalWrite(activabomba,LOW);
}

else{
  Serial.print(distancia);
   Serial.println("distancia en centimetrosccc");
   
}  
}
