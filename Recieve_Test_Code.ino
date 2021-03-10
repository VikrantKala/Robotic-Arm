
#include <RF24.h>
#include <Wire.h>
#include<Servo.h>

#define mega_pin A0 //update the pin atached to the Arduino MEGA
#define K 9         
#define L 10 
#define T A1         // Frig to be updated
#define U 5
#define I 6
#define O 3
#define P 4
#define A A5
#define B A4

RF24 radio(11,12);

byte addresses[][6] = {"1Node", "2Node"};

int data,a=1,i,c,d,j,y1,y2,l2=0;

Servo s;

void setup() {
  Serial.begin(9600);

  reset();

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(K, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(T, INPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);

  radio.begin(); 

  radio.setPALevel(RF24_PA_MIN);

  radio.openReadingPipe(1,addresses[1]);

  s.attach(mega_pin);

  s.writeMicroseconds(1500);
  delay(4000);

}
 
      
 


int forward(int a, int b, int c)          //for moving 
{                                                                   //DONE
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
  if(C>45 && c<40)                                                 //DONE
    {
      s.writeMicroseconds(a);
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

int Gripper_roll()
{                                                 //DONE
  int initial=s.readMicroseconds();
  //Serial.println("current pos =");
  //Serial.println(initial);
  forward(initial, y1, y2);
  backward(initial, y1, y2);
  return 0;
}


  void loop(){                              // VOID LOOP

analogWrite(B,150);
analogWrite(A,150);
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
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      ++i;//Serial.print("NO");
    }
   }
   else if(i>c)
   {
    while(c!=i)
    {
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      --i;//Serial.print("YES");
    }
   }
      else
     { digitalWrite(2,LOW);
      digitalWrite(3,LOW);
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
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      ++j;//Serial.print("NO");
    }
   }
   else if(j>d)
   {
    while(d!=j)
    {
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      --j;//Serial.print("YES");
    }
   }
      else
     { digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      //Serial.print("NIL");
     }
     j=d;
     }  
  else
  Serial.print("Invalid: ");
//for (int p=0;p<2;p++)
  Serial.println(G1[0]);  // X AXIS
  Serial.println(G1[1]);  // Y AXIS 
  Serial.println(G1[2]);  // FLEX 1
  Serial.println(G1[3]);  // FLEX 2
  //Serial.println(G1[1]);

  
  if(l2>=2)
  {
  Gripper_roll();   //rolling the gripper with y1 and y2 readings        //DONE
  Pwr_Window();   // power window controlled with y2                     //DONE
  flex_actuator();  //actuator controlled with flex 
  }

}
  
  
   


  //delay(1000);
 
}
