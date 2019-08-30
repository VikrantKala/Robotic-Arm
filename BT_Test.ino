int v[6]={1,2,3,4,5,6};

void setup() {
  Serial.begin(9600);


}
void loop(){

  for(int i=0;i<6;i++)
    {
    v[i]=Serial.read();
    }
}
