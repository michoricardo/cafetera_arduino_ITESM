int ledverde = 4; //Pin donde esta tu led verde
int ledrojo = 6; //Pin donde esta tu led rojo
int trigPin = 3; //Pin que usaras como tu trigger
int echoPin = 2; //Pin que usaras para el echoPin
long duration, distance; //Defines las variables de duracion y distancia

void setup() {
  Serial.begin (9600); //Establece la velocidad de datos en bits por segundo (baudios, Baud Rate) para la transmisión de datos en serie. 
  pinMode(trigPin, OUTPUT); //Defines que el pin del trigger sera salida
  pinMode(echoPin, INPUT); //Defines que el echoPin sera de entrada
  pinMode(ledverde, OUTPUT); //Defines que los leds son de salida
  pinMode(ledrojo, OUTPUT);
}

void loop() {
  int SpeedOfSound = .0343; //343m/s = 34300cm/s = 34.3cm/ms = .0343cm/us
  digitalWrite(trigPin, LOW);  //Te aseguras que cuando empiece el programa tu trigger este apagado
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); //Le das un pulso para que este funcione
  delayMicroseconds(10); //
  digitalWrite(trigPin, LOW); //Lo apagas para que detecte el pulso
  duration = pulseIn(echoPin, HIGH); //pulseIn lee el tiempo que tardo la onda en ir y volver
  distance = (duration/2)*SpeedOfSound; //Es una funcion para definir la distancia
                                        //puesto que la envio y volvio divides este tiempo entre 2
                                        //y lo multiplicas por tu velocidad del sonido en cm y us
  if (distance < 80) { //Es donde defines la distancia que tu quieres para que el led prenda verde o rojo.
    digitalWrite(ledverde,HIGH); // Si el led verde prende el rojo debe estar apagado
    digitalWrite(ledrojo,LOW);
}
  else { //Defines que si no esta dentro de esa distancia entonces esta apagado y prende rojo
    digitalWrite(ledverde,LOW); //Si el led rojo esta prendido apagas el verde
    digitalWrite(ledrojo,HIGH);
  }
  if (distance >= 400 || distance <= 2){ //Si la distancia esta fuera de los parametros del sensor entonces
    Serial.println("Fuera de rango."); //te dice que esta fuera de rango.
  }
  else {
    Serial.print(distance); //Te da en tu monitor serial la distancia
    Serial.println(" cm"); //en cm
  }
  delay(250); //tiene un retrazo de 250milisegundos cada vez que corre para que el arduino no este tan cargado y se trabe.
}
