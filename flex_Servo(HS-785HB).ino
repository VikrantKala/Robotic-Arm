#define flex_servo_pin A2
#include<Servo.h>
int q,w;
int r=1472;
Servo s2; 
void setup()
{
  Serial.begin(2400);
  s2.attach(flex_servo_pin);
  s2.writeMicroseconds(r);
  w=f2;
  
}
void loop()
{
    /*for new flex 1.2
    c.d=46
*/

//close-1592
//open-1472
q= f2;
Serial.println(q);
delay(100);
if(q>w+45 && r<1592)
{
  r=r+5;
s2.writeMicroseconds(r);
    delay(20);
}
else if(q>=w-5 && q<=w+5 && r>1472)
{
  r=r-5;
  s2.writeMicroseconds(r);
    delay(20);
}
}
