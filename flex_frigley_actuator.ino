//for 35.40 flex
/* front bend (>145)
 *  back bend ( < )
 *  normal(118-129)
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
int a;

void setup()
{
  Serial.begin(2400);
  pinMode(T, INPUT);
  pinMode(U,OUTPUT);
  pinMode(I,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
  
}
void loop()
{
a= analogRead(A1);
Serial.println(a);
delay(500);

 if(a>145 )
 {
  digitalWrite(U, LOW);
  digitalWrite(I, HIGH);
  digitalWrite(O, LOW);
  digitalWrite(P, HIGH);
 }
 else if(a>=118 && a<130)
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
