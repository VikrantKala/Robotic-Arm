#define mega_pin A0 //update the pin atached to the Arduino MEGA
//Update before Merging (Ask vikrant)
/* Y
 *  <45 FOR BACKWARD
 *  >15 FOR FORWARD
 *  y=320 and 40 
 */
#include<Servo.h>
int i;
Servo s;
int y1, y2; // TO REMOVE WHILE MERGING THE CODE

void attach_servo();
int forward(int a, int b, int c);
int backward(int a, int b, int c);

void setup() 
{
  Serial.begin(9600);
  reset();
  attach_servo();
}

void loop() {
  Serial.println("Enter y1 = ");
  y1=Serial.read();
  Serial.println("Enter y2 = ");
  y2=Serial.read();
  int initial=s.readMicroseconds();
  Serial.println("current pos =");
  Serial.println(initial);
  forward(initial, y1, y2);
  backward(initial, y1, y2);
  delay(1000);
}
void reset() //Initialising the SERVO, with the mid position
{
    int l=s.readMicroseconds();
  if(l>1500)
  {
    for(int i=l; i<=1500; i++)
    {
      s.writeMicroseconds(i);
      delay(150);
    }
  }
  else
  {
    for(int i=l; i>=1500; i--)
    {
      s.writeMicroseconds(i);
      delay(10000);
    }
  }
}

void attach_servo() // attaching the servo to the desired pin of Arduino mega which is to be inputed from the Arduino UNO
{
    s.attach(mega_pin);
}

int forward(int a, int b, int c)          //for moving 
{  
  int B = constrain(b, 1, 30);
  if(B<15 && c>320)
    {
      s.writeMicroseconds(a);
      a=a+2;
      delay(150);
      Serial.println("Current pos after forward = ");
      Serial.println(a);
    }
    return 0;
}
int backward(int a, int b, int c)          //for moving 
{  
  int C = constrain(b, 0, 50);
  if(C>45 && c<40)
    {
      s.writeMicroseconds(a);
      a=a-2;
      delay(150);
      Serial.println("Current pos after backward = ");
      Serial.println(a);
    }
    return 0;
}
