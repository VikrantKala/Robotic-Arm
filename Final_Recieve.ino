
/*  
 
PW:  PWM - A1 K - 9 L - 10
BIG ACT1: PWM - A4 p - 20 n - 21
BIG ACT2: PWM - A5 p - 24 n - 25
S1 : Signal - A0
S2 : Signal - A2
2 Frigly: U(1) - 5 I(2) - 6 O(3) - 3 P(4) - 4
CE , CSN - 11 , 12

*/
#include <RF24.h>
#include <Wire.h>
#include<Servo.h>

#define mega_pin A0 //update the pin atached to the Arduino MEGA
#define K 9         
#define L 10 
#define U 5
#define I 6
#define O 3
#define P 4
#define A A5
#define B A4
#define flex_servo_pin A2
#define ACT1 20
#define ACT2 21
#define ACT3 24
#define ACT4 25
#define R A1

RF24 radio(11,12);

byte addresses[][6] = {"1Node", "2Node"};

int data,a=1,i,c,d,j,y1,y2,l2=0,f1,f2,q,w,r=1472,w=190,g=125,h=125;  //190 and 125 is the initial value of the NEW FLEX 1.2 and the old one;

Servo s1,s2;

void setup() {
  Serial.begin(9600);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(L,OUTPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
  pinMode(R,OUTPUT);

  radio.begin(); 

  radio.setPALevel(RF24_PA_MIN);

  radio.openReadingPipe(1,addresses[1]);

  s1.attach(mega_pin);
  s1.writeMicroseconds(1500);
  
  delay(2000);
  
  s2.attach(flex_servo_pin);
  s2.writeMicroseconds(r);
  
  delay(2000);
  
  
  

}
 
      
 


int forward(int a, int b, int c)          //for moving 
{                                                                   //DONE
  int B = constrain(b, 1, 30);
  if(B<15 && c>320)
    {
      s1.writeMicroseconds(a);
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
  if(C>45 && c<40)                                                 //DONE
    {
      s1.writeMicroseconds(a);
      a=a-2;
      delay(150);
      Serial.println("Current pos after backward = ");
      Serial.println(a);
    }
    return 0;
}
int Pwr_Window()                                            //DONE
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
    digitalWrite(K, LOW);
    digitalWrite(L, LOW);
  }
  return 0;
}

int flex_servo()
{
  /*for new flex 1.2
    c.d=46                                                              //DONE
*/

//close-1592
//open-1472
q= ::f2;
Serial.println(q);
delay(100);
if((q>(w+45)) && r<(1592))
{
  r=r+5;
s2.writeMicroseconds(r);
    delay(20);
}
else if((q>=(w-5)) && (q<=(w+5)) && (r>1472))
{
  r=r-5;
  s2.writeMicroseconds(r);
    delay(20);
}
  return 0;
}
int flex_frig()
{
/*
for green-grey wired flex                                                   //DONE
c.d=33
 */
//5 input
//6 input
//3 input
//4 input
g= ::f1;
Serial.println(g);

 if(g>(h+32) )
 {
  digitalWrite(U, LOW);
  digitalWrite(I, HIGH);
  digitalWrite(O, LOW);
  digitalWrite(P, HIGH);
   delay(20);
 }
 else if((g>=(h-5)) && (g<(h+5)))
 {
  digitalWrite(U, HIGH);
  digitalWrite(I,LOW);
  digitalWrite(O, HIGH);
  digitalWrite(P,LOW);
   delay(20);
 }
 else
 {
  digitalWrite(U,LOW);
  digitalWrite(I,LOW);
  digitalWrite(O,LOW);
  digitalWrite(P,LOW);
   delay(20);
 }

  return 0;
}


int Gripper_roll()
{                                                 //DONE
  int initial=s1.readMicroseconds();
  //Serial.println("current pos =");
  //Serial.println(initial);                                           
  forward(initial, y1, y2);
  backward(initial, y1, y2);
  return 0;
}


  void loop(){                                                    // VOID LOOP

analogWrite(B,150);
analogWrite(A,150);
analogWrite(R,150);
  radio.startListening();
  
  if(radio.available())
  {int G1[8];
    radio.read( &G1, sizeof(G1) );
  
  if(a==1)
  {Serial.print("Slave1: ");
  --a; c=G1[0]; ::y1=G1[1]; ++l2;
  c=constrain(c,0,90);
   Serial.print(c);
   Serial.println();
      if(c>i)
   {
    while(c!=i)
    {
      digitalWrite(ACT1,HIGH);
      digitalWrite(ACT2,LOW);
      ++i;//Serial.print("NO");
    }
   }
   else if(i>c)
   {
    while(c!=i)
    {
      digitalWrite(ACT1,LOW);
      digitalWrite(ACT2,HIGH);
      --i;//Serial.print("YES");
    }
   }
      else
     { digitalWrite(ACT1,LOW);
      digitalWrite(ACT2,LOW);
      //Serial.print("NIL");
     }
     i=c;
    }
  else if(a==0)
  {Serial.print("Slave2: ");++a;
  d=G1[0]; ::y2=G1[1]; ++l2;
  d=constrain(d,0,90);
   Serial.print(d);
   Serial.println();
      if(d>j)
   {
    while(d!=j)
    {
      digitalWrite(ACT3,HIGH);
      digitalWrite(ACT4,LOW);
      ++j;//Serial.print("NO");
    }
   }
   else if(j>d)
   {
    while(d!=j)
    {
      digitalWrite(ACT3,LOW);
      digitalWrite(ACT4,HIGH);
      --j;//Serial.print("YES");
    }
   }
      else
     { digitalWrite(ACT3,LOW);
      digitalWrite(ACT4,LOW);
      //Serial.print("NIL");
     }
     j=d;
     }  
  else
  Serial.print("Invalid: ");
//for (int p=0;p<2;p++)
  Serial.println(G1[0]);  // X AXIS
  Serial.println(G1[1]);  // Y AXIS 
  Serial.println(G1[2]);  // FLEX 1 SERVO 
  Serial.println(G1[3]);  // FLEX 2 FRIGLY
  //Serial.println(G1[1]);

  ::f1 = G1[2]; // SERVO
  ::f2 = G2[3]; // FRIGLY
  if(l2>=2)
  {
  Gripper_roll();   //rolling the gripper with y1 and y2 readings       //DONE
  Pwr_Window();     //power window controlled with y2                   //DONE
  flex_frig();      //actuator controlled with flex 1                   //DONE
  flex_servo();     //opening and closing gripper with flex 2           //DONE
  
  }

}
  
  
   


  //delay(1000);
 
}
