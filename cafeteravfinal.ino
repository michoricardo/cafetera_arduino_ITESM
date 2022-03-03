#include <Servo.h>

/*
Conexiones:
 - TRIG al pin D12
 - ECHO al pin D13
*/


#define PIN_TRIG 12 // Es el pin donde conectas el trig
#define PIN_ECO  13 //Es el pin donde conectas el echo (PIN DIGITAL)

int presion=3;
int sw1=4;
int sw2=5;
int lleno=6;
int activabomba=7;
Servo miservo;
Servo miservo2;


void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600);  //Empieza la comunicación serial ( lo necesitas para ver la distancia) 
  
  //cuando lo corras le pones en HERRAMIENTAS  Y LUEGO LE PICAS EN MONITOR SERIE para que te esté diciendo todas las mediciones del sensor ultrasónico en tiempo real
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT); //Pones el pin del trigger como output para mandar la onda sonora
  pinMode(PIN_ECO, INPUT); //pones el pin de echo como input para recibir la onda sonora
  pinMode(presion, INPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(lleno,OUTPUT);
  pinMode(activabomba,OUTPUT);
  miservo.attach(9);
  miservo2.attach(10);
}

void loop() { //ciclo para que se repita todo el tiempo
  long duracion, distancia;  // Variables para sacar la duración y distancia del disparo
  
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  //aquí te aseguras de tener el trigger sin disparo
  delayMicroseconds(2); //delay de tiempo ( osea una pausita)
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente. aquí mandas el disparo con el trigger osea el emisor 
  delayMicroseconds(10);        // Duracion del pulso----- pausita
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente aquí apagas el trigger
  
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);  //aquí prendes el echo (receptor) para que reciba la información que mandó el trigger.
  
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29; //con esta formula sacas la distancia en centímetros.
  
  if(digitalRead(sw1)==HIGH &&digitalRead(presion)==HIGH){
    //ACTIVO LOS SERVOS Y LA BOMBA CON RELE 
   digitalWrite(activabomba,HIGH);
   delay(1000);
   miservo.write(180);
   delay(1000);
   miservo.write(0);
   delay(1000);
   miservo.write(180);
   
   
}
else{
  digitalWrite(activabomba,LOW);
  miservo.write(180);
  
}
  if(digitalRead(sw2)==HIGH &&digitalRead(presion)==HIGH){
    //ACTIVO LOS OTROS SERVOS Y LA BOMBA CON RELE
    digitalWrite(activabomba,HIGH);
    delay(7000);
    miservo2.write(0);
    delay(1000);
    miservo2.write(180);
    delay(1000);
    miservo2.write(0);
    
  }


else{
  digitalWrite(activabomba,LOW);
 miservo.write(180); 
}
/* Imprimir resultados a la terminal serial */
  if (distancia <=8){
    Serial.println("Ya está lleno el vaso!!!!!!!!!!");
    digitalWrite(activabomba,LOW);
        
  }
  else {
    Serial.print(distancia);
    Serial.println("= distancia en  cm");
    digitalWrite(activabomba,HIGH);
    
  }
  
  // Retardo para disminuir la frecuencia de las lecturas
  delay(500);  
}

