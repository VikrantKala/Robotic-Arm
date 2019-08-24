//for 35.40 flex, CHANGE THE READINGS ACCORDINGLY
int a;

void setup()
{
  Serial.begin(2400);
  pinMode(A1, INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
}
void loop()
{
a= analogRead(A1);
Serial.println(a);
delay(500);
/* front bend (>145)
 *  back bend ( < )
 *  normal(118-129)
 */
//5 input
//6 input
//3 input
//4 input
 if(a>145 )
 {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
 }
 else if(a>=118 && a<130)
 {
  digitalWrite(5, HIGH);
  digitalWrite(6,LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4,LOW);
 }
 else
 {
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
 }

}
