#include <Servo.h>            // include servo.h library
#define trigPin 6 //Define the HC-SE04 triger on pin 6 on the arduino
#define echoPin 5 //Define the HC-SE04 echo on pin 5 on the arduino

Servo myservo_sensor;

int pos_sensor = 0; 
int smos;
int metel;


void setup()
{
  Serial.begin (9600);
  myservo_sensor.attach(10);//connect servo to pin 8
  myservo_sensor.write(0); 
  pinMode(13,INPUT); //input pin coming from soil sensor
  pinMode(9,INPUT); //input pin coming from metel sensor(black wire)
  pinMode(trigPin, OUTPUT); //set the trigpin to output
  pinMode(echoPin, INPUT); //set the echopin to input
}

void loop() { 

smos = digitalRead(13); 
metel =LOW;
delay(1000);
metel = digitalRead(9);

Serial.print("\n Waiting"); 


if(metel == LOW){
   Serial.print("\nMETAL"); 
   myservo_sensor.write(75); 
 }
if(smos == LOW)  { 
   Serial.print("\nWET"); 
   myservo_sensor.write(175); 
  }
else{
   int duration, distance; //Define two intregers duration and distance to be used to save data
   digitalWrite(trigPin, HIGH); //write a digital high to the trigpin to send out the pulse
   delayMicroseconds(500); //wait half a millisecond
   digitalWrite(trigPin, LOW); //turn off the trigpin
   duration = pulseIn(echoPin, HIGH); //measure the time using pulsein when the echo receives a signal set it to high
   distance = (duration/2) / 29.1; //distance is the duration devided by 2 becasue the signal traveled from the trigpin then back to the echo pin, then divide by 29.1 to convert to centimeters

   if (distance < 04) {
   Serial.print("\nDRY"); 
   myservo_sensor.write(0);
   }
  }
}
