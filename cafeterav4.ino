#include <Servo.h>  //Load Servo Library
int trigPin=13; //Sensor Trip pin connected to Arduino pin 13
int echoPin=11;  //Sensor Echo pin connected to Arduino pin 11
int servoControlPin=6; //Servo control line is connected to pin 6
float pingTime;  //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=776.5; //Speed of sound in miles per hour when temp is 77 degrees.
float servoAngle; //Variable for the value we want to set servo to.
 
Servo myPointer;  //Create a servo object called myPointer
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servoControlPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myPointer.attach(servoControlPin);  //Tell arduino where the servo is attached.
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(330); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(300); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(300); //Delay in low state
  
  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  targetDistance=targetDistance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*63360;    //Convert miles to inches by multipling by 63360 (inches per mile)
  
  Serial.print("The Distance to Target is: ");
  Serial.print(targetDistance);
  Serial.println(" inches");
  
  servoAngle = (106./7.) * targetDistance + 37; //Calculate Servo Angle from targetDistance
  myPointer.write(servoAngle); //write servoAngle to the servo
  Serial.println(servoAngle);
  delay(100); //delay tenth of a  second to slow things down a little.
}

