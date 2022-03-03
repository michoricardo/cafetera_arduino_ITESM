#include <Servo.h>
#define trigPin 2
#define echoPin 3
Servo servo;
void setup(){
  Serial.begin(9600);
  Serial.print("Mesafe olcme...!");
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  servo.attach(6);
}
void loop(){
  long duration,distance;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration/58.2;
  delay(29);
  Serial.println(distance);
  distance=map(distance,6,13,0,180);
  servo.write(distance);
}
