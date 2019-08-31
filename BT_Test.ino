int v[6]={1,2,3,4,5,6},p=0;
void setup() {
 Serial.begin(9600);
}

void loop() {
 if(p==0)
    Serial.write(v[0]); 
    else if(p==1)
    Serial.write(v[1]);
    else if(p==2)
    Serial.write(v[2]);
    else if(p==3)
    Serial.write(v[3]); 
    else if(p==4)
    Serial.write(v[4]);
    else if(p==5)
    Serial.write(v[5]);
    
    p++;

   if(p>6)
    p=0;
    
    
    delay(20);

}
