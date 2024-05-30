void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT); //LDR
pinMode(5,INPUT); // IR sensor
pinMode(4,OUTPUT); // LED
pinMode(8,OUTPUT); // buzzer
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
int intruder = digitalRead(5); //Input from IR sensor
int ldr = analogRead(A0); //Input from LDR
Serial.print("intruder: "); 
Serial.println(intruder); //prints the value from pin 5
Serial.print("ldr: ");
Serial.println(ldr); //prints the value from pin A0
//delay(500);

if(ldr<100) //low ambient light
{
  digitalWrite(4,HIGH);
  }
if(ldr>=100) //high ambient light
{
  digitalWrite(4,LOW);
  }
//To turn ON/OFF the LED wrt the ambient light
if(intruder==0) //condition for intruder
{
  digitalWrite(8,LOW);
  }
if(intruder==1)
{
 digitalWrite(8,HIGH); 
  } 
 }   //To turn ON/OFF the Buzzer( Intruder presence )
