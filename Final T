
#include <RF24.h>
#include<Wire.h>

// ce = 6 || csn = 10

RF24 radio(6, 10);

byte addresses[][6] = {"1Node", "2Node"};
 const int MPU_addr=0x68,MPU2=0x69; 
 
 int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,x,y,z;
 
int minVal=265, maxVal=402, data;




int v[10]; 

void setup() {
  
 // Serial.println("THIS IS THE TRANSMITTER CODE - YOU NEED THE OTHER ARDIUNO TO SEND BACK A RESPONSE");

  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  
 // radio.setDataRate(RF24_2MBPS);

  
  //radio.setChannel(124);
   
  radio.openWritingPipe(addresses[1]);


  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  
  Wire.begin(); 
  Wire.beginTransmission(MPU2); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  Serial.begin(9600); } 
 
  void loop(){ 
    Serial.print("First\n");
 angles(MPU_addr);
   Serial.println("--------------------");

Serial.print("Second \n");
angles(MPU2);
Serial.print("----------------------------\n");
 
 
  delay(1000);
}

void angles(const int MPU)
  {
    Wire.beginTransmission(MPU); 
    Wire.write(0x3B); 
    Wire.endTransmission(false); 
    Wire.requestFrom(MPU,14,true); 
    AcX=Wire.read()<<8|Wire.read(); 
    AcY=Wire.read()<<8|Wire.read(); 
    AcZ=Wire.read()<<8|Wire.read(); 
    int xAng = map(AcX,minVal,maxVal,-90,90); 
    int yAng = map(AcY,minVal,maxVal,-90,90); 
    int zAng = map(AcZ,minVal,maxVal,-90,90);

x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

//Serial.print("AngleX= "); Serial.println(x);
//
//Serial.print("AngleY= "); Serial.println(y);

//Serial.print("AngleZ= "); Serial.println(z); 

v[0]=x;
v[1]=y;
v[2]=analogRead(A1);
v[3]=analogRead(A2);
 radio.stopListening(); 
  radio.write( &v, sizeof(v) );
  Serial.print("x: ");
  Serial.println(x);
  Serial.print("y: ");
  Serial.println(y);  
  Serial.print("Flex 1:");
  Serial.println(v[2]);
  Serial.print("Flex 2:");
  Serial.println(v[3]);  
  //delay(1000);
 
}
