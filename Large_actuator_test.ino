#include <RF24.h>

{//Large Linear Actuator
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
}

RF24 radio(7, 8);

byte addresses[][6] = {"", "2Node"};
int v[6];

void setup() {
  Serial.begin(9600);
  pinMode(Large_actuator_1_1,OUTPUT);
  pinMode(Large_actuator_1_2,OUTPUT);
  pinMode(Large_actuator_2_1,OUTPUT);
  pinMode(Large_actuator_2_2,OUTPUT);
  pinMode(Hercules_pwm_1,OUTPUT);
  pinMode(Hercules_pwm_2,OUTPUT);
  radio.begin();  
  radio.setPALevel(RF24_PA_MIN);
 
  radio.openReadingPipe(1,addresses[1]);
   }
 
  void loop(){ 
  
  analogWrite(Hercules_pwm_1,150);
  analogWrite(Hercules_pwm_2,150);
  radio.startListening();
     
  if(radio.available())
  {
    radio.read( &v, sizeof(v) );
    //v[0]=constrain(v[0], , ); // USE IF NECESSARY
    if(v[0]>angle_forward_1 && v[0]<angle_max_1)
    {
      digitalWrite(Large_actuator_1_1, HIGH);
      digitalWrite(Large_actuator_1_2, LOW);
      delay(20);
    }
    else if(v[0]<angle_backward_1 && v[0]>angle_min_1)
    {
      digitalWrite(Large_actuator_1_1, LOW);
      digitalWrite(Large_actuator_1_2, HIGH);
      delay(20);
    }
    else if(v[0]<=angle_forward_1 && v[0]>=angle_backward_1)
    {
      digitalWrite(Large_actuator_1_1, LOW);
      digitalWrite(Large_actuator_1_2, LOW);
      delay(20);
    }

    //v[2]=constrain(v[2], , ); // USE IF NECESSARY
    if(v[2]>angle_forward_2 && v[2]<angle_max_2)
    {
      digitalWrite(Large_actuator_2_1, HIGH);
      digitalWrite(Large_actuator_2_2, LOW);
      delay(20);
    }
    else if(v[2]<angle_backward_2 && v[2]>angle_min_2)
    {
      digitalWrite(Large_actuator_2_1, LOW);
      digitalWrite(Large_actuator_2_2, HIGH);
      delay(20);
    }
    else if(v[2]<=angle_forward_2 && v[2]>=angle_backward_2)
    {
      digitalWrite(Large_actuator_2_1, LOW);
      digitalWrite(Large_actuator_2_2, LOW);
      delay(20);
    }
    delay(1000);
  }
