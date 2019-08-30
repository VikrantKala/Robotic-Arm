void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}
int a[20],i=0;
void loop() {
  if(Serial.available()>0)
  {
   if(i<6){
     a[i]=Serial.read();
    
     Serial.println(a[i]);
     ++i;
   }
    i=0;
  }
  
}
