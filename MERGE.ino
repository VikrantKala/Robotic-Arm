#define mega_pin A0 //update the pin atached to the Arduino MEGA
#define K 9
#define L 10 
#define T A1
#define U 5
#define I 6
#define O 3
#define P 4
/* y1=<45 FOR BACKWARD and >15 FOR FORWARD
 *  y2=320 and 40*/
#include<Servo.h>
int i;

Servo s;
//int y1, y2; Input of Y-AXIS from FLEX1 AND FLEX2

void attach_servo();
int forward(int a, int b, int c);
int backward(int a, int b, int c);
int Pwr_Window();
int flex_actuator();
int Gripper_roll_flex();
void setup() 
{
  Serial.begin(9600);
  reset();
  attach_servo();
  pinMode(K, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(T, INPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
}

void loop() {
  Gripper_roll_flex();  
  Pwr_Window();
  flex_actuator();
  
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
int Pwr_Window()
{
  if(y2<320 && y2>220)
  {
  digitalWrite(K, HIGH);
  digitalWrite(L, LOW);
  }
  else if(y2>40 && y2<140)
  {
  digitalWrite(K, LOW);
  digitalWrite(L, HIGH);
  }
  else if(y2>319 && y2<39)
  {
    digitalWrite(K, HIGH);
    digitalWrite(L, HIGH);
  }
  return 0;
}

int flex_actuator()
{
  int b= analogRead(T);
Serial.println(b);
delay(500);
/* front bend (>145)
 *  back bend ( < )
 *  normal(118-129)
 */
//5 input
//6 input
//3 input
//4 input
 if(b>145 )
 {
  digitalWrite(U, LOW);
  digitalWrite(I, HIGH);
  digitalWrite(O, LOW);
  digitalWrite(P, HIGH);
 }
 else if(b>=118 && b<130)
 {
  digitalWrite(U, HIGH);
  digitalWrite(I,LOW);
  digitalWrite(O, HIGH);
  digitalWrite(P,LOW);
 }
 else
 {
  digitalWrite(U,LOW);
  digitalWrite(I,LOW);
  digitalWrite(O,LOW);
  digitalWrite(P,LOW);
 }
 return 0;
}

int Gripper_roll_flex()
{
  int initial=s.readMicroseconds();
  Serial.println("current pos =");
  Serial.println(initial);
  forward(initial, y1, y2);
  backward(initial, y1, y2);
  return 0;
}
