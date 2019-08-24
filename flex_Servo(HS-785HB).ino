//28.5 flex
//close-1592
//open-1472
#include<Servo.h>
int a,c;
int b=1472;
Servo s; 
void setup()
{
  Serial.begin(2400);
  s.attach(A2);
  pinMode(A1, INPUT);
  s.writeMicroseconds(b);
  c=analogRead(A1);
  
}
void loop()
{
a= analogRead(A1);
Serial.println(a);
delay(100);
if(a>c+15 && b<1592)
{
  b=b+5;
s.writeMicroseconds(b);
}
else if(a>=c-4 && a<=c+4 && b>1472)
{
  b=b-5;
  s.writeMicroseconds(b);
}
}
