// 
/*
for green-grey wired flex
c.d=33
 */
//5 input
//6 input
//3 input
//4 input
#define T A1
#define U 5
#define I 6
#define O 3
#define P 4
int g,h;

void setup()
{
  Serial.begin(2400);
  pinMode(T, INPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
  b=analogRead(T);
}
void loop()
{
a= analogRead(T);
Serial.println(g);
delay(500);

 if(g>h+32 )
 {
  digitalWrite(U, LOW);
  digitalWrite(I, HIGH);
  digitalWrite(O, LOW);
  digitalWrite(P, HIGH);
 }
 else if(g>=h-5 && g<h+5)
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

}
