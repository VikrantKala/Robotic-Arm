//28.5 flex
#include<Servo.h>
int a;
int b=600;
Servo s; 
void setup()
{
  Serial.begin(2400);
  s.attach(A2);
  pinMode(A1, INPUT);
  pinMode(A2,OUTPUT);
  s.writeMicroseconds(b);
  
}
void loop()
{
a= analogRead(A1);
Serial.println(a);
delay(100);
if(a>172 && b<658)
{
  b=b+2;
s.writeMicroseconds(b);
}
else if(a>=151 && a<=158 && b>600)
{
  b=b-2;
  s.writeMicroseconds(b);
}
}
