#define sda_max 0  //later to be changed
#define sda_min 100 //later to be changed
#include<Servo.h>
int sda_pin=A4; //the sda pin on the master, which is Arduino UNO
int n; //to write the microseconds in the servo
Servo s;

void setup() {
  Serial.begin(9600);
  s.writeMicroseconds(1500); //initializing the servo
  s.attach(7); // attaching the servo to the desired pin of Arduino mega which is to be inputed from the Arduino UNO
  }

void loop() {
  int sensor_val = analogRead(sda_pin);
  n = map(sensor_val, sda_min, sda_max, 600, 2400);
  s.writeMicroseconds(n);
  Serial.println(n);
  
}
