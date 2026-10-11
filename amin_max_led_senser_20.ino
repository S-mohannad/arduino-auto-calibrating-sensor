int x=0,z=0;
int max=0;
int min=1023;
void setup() {
Serial.begin(9600);
pinMode(7,OUTPUT);
pinMode(12,OUTPUT);
delay(1000);
tone(12,250,100);
while(millis()<9000){
x=analogRead(A0);
max=max(max,x);
min=min(min,x);}
tone(12,950,100);
Serial.print("the min is:  ");
Serial.print(min);
Serial.print("   ");
Serial.print("the max is:  ");
Serial.println(max);
z=min+max;
z=z/2;
Serial.print("the z is:  ");
Serial.print(z);
}
void loop() {
x=analogRead(A0);
if (x>z)
{digitalWrite(7,LOW);}
else
{digitalWrite(7,HIGH);}
}