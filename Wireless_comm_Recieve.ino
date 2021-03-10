#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>


RF24 radio(7, 8);

byte addresses[][6] = {"1Node", "2Node"};

int data,a=1,i=0,c,d,j=0;



void setup() {
  Serial.begin(9600);
 // Serial.println("THIS IS THE TRANSMITTER CODE - YOU NEED THE OTHER ARDIUNO TO SEND BACK A RESPONSE");

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  //pinMode(A0,OUTPUT);
  pinMode(11,OUTPUT);
  radio.begin();
  
  radio.setPALevel(RF24_PA_MIN);
  
 // radio.setDataRate(RF24_2MBPS);
  
  //radio.setChannel(124);

  radio.openReadingPipe(1,addresses[1]);
  
}
 
  void loop(){ 
//analogWrite(A0,150);
analogWrite(11,150);
  radio.startListening();
  
 // int G2;
 
  if(radio.available())
  {int G1[4];
    radio.read( &G1, sizeof(G1) );
  
  if(a==1)
  {
    --a;
    c=G1[0];
    c=constrain(c,0,90);
    Serial.print("Slave1: ");
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
     { 
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      //Serial.print("NIL");
     }
     i=c;
   }
  else if(a==0)
   {
    Serial.print("Slave2: ");++a;
    d=G1[0];
    d=constrain(d,0,90);
    Serial.print(d);
    Serial.println();
  if(d>j)
   {
      while(d!=j)
       {
          digitalWrite(5,HIGH);
          digitalWrite(4,LOW);
          ++j;Serial.print("NO");
       }
   }
  else if(j>d)
   {
    while(d!=j)
      {
       digitalWrite(5,LOW);
       digitalWrite(4,HIGH);
       --j;Serial.print("YES");
      }
   }
  else
   { 
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    Serial.print("NIL");
   }
     j=d;
 }  
  else
  Serial.print("Invalid: ");
  Serial.println(G1[0]);
  Serial.println(G1[1]);
//  radio.read( &G2, sizeof(int) );
//   Serial.print("Slave2: ");
//  Serial.println(G2);
}
  
  
   
  

  //delay(1000);
 
}
