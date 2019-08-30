#include <RF24.h>
#include <Servo.h>

//Large Linear Actuator
#define Large_actuator_1_1 2
#define Large_actuator_1_2 3
#define Large_actuator_2_1 5
#define Large_actuator_2_2 4
#define Hercules_pwm_1 A0
#define Hercules_pwm_2 A1
#define angle_forward_1 30
#define angle_max_1 90
#define angle_backward_1 330
#define angle_min_1 270
#define angle_forward_2 30
#define angle_max_2 90
#define angle_backward_2 330
#define angle_min_2 270
#define LA_feedback A7
#define LA_MAX 800

//Power Window
#define K 9
#define L 10 
#define y2_max 40
#define y2_min 320
#define Hercules_pwm_pw 6

//Servo_Gripper_Rotation
#define s_360_pin A4
#define s_360_initial 1500
#define Servo_rotation_speed 25

//Frigliee actuators
#define U 40
#define I 42
#define O 46
#define P 48

//Flex Servo(Hs785hb)
#define flex_servo_pin A7
int servo_initial = 1500;
#define servo_close 1592
#define servo_open 1472
#define servo_speed 20

RF24 radio(7, 8);

byte addresses[][6] = {"", "2Node"};
int v[6];
Servo s_360, s_flex;
int g,h,x,t=0,q,w,m=0;

void setup() {
  Serial.begin(9600);
  pinMode(Large_actuator_1_1,OUTPUT);
  pinMode(Large_actuator_1_2,OUTPUT);
  pinMode(Large_actuator_2_1,OUTPUT);
  pinMode(Large_actuator_2_2,OUTPUT);
  pinMode(Hercules_pwm_1,OUTPUT);
  pinMode(Hercules_pwm_2,OUTPUT);
  pinMode(Hercules_pwm_pw,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(L,OUTPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
  
  s_360.attach(s_360_pin);
  s_360.writeMicroseconds(s_360_initial);
  s_flex.attach(flex_servo_pin);
  s_flex.writeMicroseconds(servo_initial);
  delay(20);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
 
  radio.openReadingPipe(1,addresses[1]);
   }
 
  void loop(){ 
  
  analogWrite(Hercules_pwm_1,150);
  analogWrite(Hercules_pwm_2,150);
  analogWrite(Hercules_pwm_pw,150);
  radio.startListening();
     
  if(radio.available())
  {
    radio.read( &v, sizeof(v) );
    Large_actuators(v);
    Power_window(v);
    Servo_Gripper_Rotation(v[1], v[3]);
    Flex_frig(v[4]);
    Flex_servo(v[5]);
  }
    delay(1000);
  }


int  Large_actuators(int v[])
  {
    //v[0]=constrain(v[0], , ); // USE IF NECESSARY
    if(v[0]>angle_forward_1 && v[0]<angle_max_1)
    {
      if(analogRead(LA_feedback)<LA_MAX)
      {
      digitalWrite(Large_actuator_1_1, HIGH);
      digitalWrite(Large_actuator_1_2, LOW);
      }
      else
      {
      digitalWrite(Large_actuator_1_1, LOW);
      digitalWrite(Large_actuator_1_2, LOW);
      }
    }
    else if(v[0]<angle_backward_1 && v[0]>angle_min_1)
    {
      digitalWrite(Large_actuator_1_1, LOW);
      digitalWrite(Large_actuator_1_2, HIGH);
    }
    else if(v[0]<=angle_forward_1 && v[0]>=angle_backward_1)
    {
      digitalWrite(Large_actuator_1_1, LOW);
      digitalWrite(Large_actuator_1_2, LOW);
    }

    //v[2]=constrain(v[2], , ); // USE IF NECESSARY
    if(v[2]>angle_forward_2 && v[2]<angle_max_2)
    {
      if(analogRead(LA_feedback)<LA_MAX)
      {
      digitalWrite(Large_actuator_2_1, HIGH);
      digitalWrite(Large_actuator_2_2, LOW);
      }
      else
      {
      digitalWrite(Large_actuator_2_1, LOW);
      digitalWrite(Large_actuator_2_2, LOW);
      }
    }
    else if(v[2]<angle_backward_2 && v[2]>angle_min_2)
    {
      digitalWrite(Large_actuator_2_1, LOW);
      digitalWrite(Large_actuator_2_2, HIGH);
    }
    else if(v[2]<=angle_forward_2 && v[2]>=angle_backward_2)
    {
      digitalWrite(Large_actuator_2_1, LOW);
      digitalWrite(Large_actuator_2_2, LOW);
    }
    return 0;
  }

  int Power_window(int v[6])
  {
    if(v[3]<=y2_min && v[3]>220)
  {
    digitalWrite(K, HIGH);
    digitalWrite(L, LOW);
    delay(20);
  }
  else if(v[3]>=y2_max && v[3]<140)
  {
    digitalWrite(K, LOW);
    digitalWrite(L, HIGH);
    delay(20);
  }
  else if(v[3]>y2_min && v[3]<y2_max)
  {
    digitalWrite(K, HIGH);
    digitalWrite(L, HIGH);
    delay(20);
  }
  }

int Servo_Gripper_Rotation(int y1, int y2)
  {
    int current=s_360.readMicroseconds();
    Serial.println("current pos =");
    Serial.println(current);
    forward(current, y1, y2);
    backward(current, y1, y2);
    return 0;
  }
 
  int forward(int a, int b, int c)          //for moving forward
{  
  int B = constrain(b, 1, 30);
  if(B<15 && c>320)
    {
      s_360.writeMicroseconds(a);
      a=a+Servo_rotation_speed;
    }
    return 0;
}
int backward(int a, int b, int c)          //for moving backward
{  
  int C = constrain(b, 0, 50);
  if(C>45 && c<40)
    {
      s_360.writeMicroseconds(a);
      a=a-Servo_rotation_speed;
    }
    return 0;
}

int Flex_frig(int a)
{
    x=a;
  if(t==0)
  {
    g=x;
    ++t;
  }
  h=a;
 if(g>(h+32) )
 {
  digitalWrite(U, LOW);
  digitalWrite(I, HIGH);
  digitalWrite(O, LOW);
  digitalWrite(P, HIGH);
 }
 else if(g>=(h-5) && g<(h+5))
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
  digitalWrite(P,LOW);;
 }
  return 0;
}

int Flex_servo(int s)
{
if(m==0)
{
  w=s;
  m++;
}
q= s;
if(q>w+45 && servo_initial<servo_close)
{
  servo_initial=servo_initial+servo_speed;
  s_flex.writeMicroseconds(servo_initial);
}
else if(q>=w-5 && q<=w+5 && servo_initial>servo_open)
{
  servo_initial = (servo_initial-servo_speed);
  s_flex.writeMicroseconds(servo_initial);
}
  return 0;
}
