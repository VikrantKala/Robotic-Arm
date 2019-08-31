
#include<Wire.h>

#define flex_pin_1 A1
#define flex_pin_2 A2


byte addresses[][6] = {"", "2Node"};
const int MPU1=0x68,MPU2=0x69;  
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,x,y,z,p;
int x1,y1,x2,y2;
int minVal=265, maxVal=402;

int v[6]; 

void setup() {
  


  Wire.begin(); 
  Wire.beginTransmission(MPU1); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  
  Wire.begin(); 
  Wire.beginTransmission(MPU2); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  Serial.begin(9600); 
  Serial1.begin(9600);
  } 
 
  void loop(){ 
    Serial.print("First\n");
    angles(MPU1, x1, y1);
    Serial.println("--------------------");

    Serial.print("Second \n");
    angles(MPU2, x2, y2);
    Serial.print("----------------------------\n");
   
    v[0]=x1;v[1]=y1;v[2]=x2;v[3]=y2;

    v[4]=analogRead(flex_pin_1);
    v[5]=analogRead(flex_pin_2);
    
     if(p==0)
    Serial1.write(v[0]); 
    else if(p==1)
    Serial1.write(v[1]);
    else if(p==2)
    Serial1.write(v[2]);
    else if(p==3)
    Serial1.write(v[3]); 
    else if(p==4)
    Serial1.write(v[4]);
    else if(p==5)
    Serial1.write(v[5]);
    
    p++;

   if(p>6)
    p=0;
    
    delay(20);
}

void angles(const int MPU, int &a, int &b)
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

a=x;
b=y;
 }
