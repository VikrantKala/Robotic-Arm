
// CODE FOR POWER WINDOW

#define K 9
#define L 10 
int y2;
//y2(range)=320 and 40 


void setup() {
  Serial.begin(9600);
  pinMode(K, OUTPUT);
  pinMode(L, OUTPUT);
}

void loop() {
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
    digitalWrite(K, HIGH);
    digitalWrite(L, HIGH);
  }

}
