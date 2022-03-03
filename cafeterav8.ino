#include <Servo.h>

/****************************************************************
 Sensor de Ultrasonico HC-SR04 con Arduino
*****************************************************************
Conexiones:
 - TRIG al pin D12
 - ECHO al pin D13

Notas:
  
  Raul Alvarez Torrico | Agosto de 2013
  http://www.TecBolivia.com  | info@tecbolivia.com
****************************************************************/

#define PIN_TRIG 12
#define PIN_ECO  13

int presion= 3;
int sw1=4;
int sw2=5;
int lleno=6;
int activabomba=7;
Servo miservo;
Servo miservo2;


void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600);  
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
  pinMode(presion, INPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(lleno,OUTPUT);
  pinMode(activabomba,OUTPUT);
  miservo.attach(9);
  miservo.attach(10);
}

void loop() {
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
  
  if(digitalRead(sw1)&&digitalRead(presion)==HIGH){
    //ACTIVO LOS SERVOS Y LA BOMBA CON RELE 
   digitalWrite(activabomba,HIGH);
   miservo.write(180);
   
}
else{
  digitalWrite(activabomba,LOW);
  miservo.write(0);
}
  if(digitalRead(sw2)&&digitalRead(presion)==HIGH){
    //ACTIVO LOS OTROS SERVOS Y LA BOMBA CON RELE
    digitalWrite(activabomba,HIGH);
    miservo2.write(180);
  }


else{
  digitalWrite(activabomba,LOW);
  miservo2.write(0);
}
/* Imprimir resultados a la terminal serial */
  if (distancia <=7){
    Serial.println("Ya está lleno el vaso!!!!!!!!!!");
    digitalWrite(lleno,HIGH);
        
  }
  else {
    Serial.print(distancia);
    Serial.println("= distancia en  cm");
    digitalWrite(lleno,LOW);
    
  }
  
  // Retardo para disminuir la frecuencia de las lecturas
  delay(500);  
}

