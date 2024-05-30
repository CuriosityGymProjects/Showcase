int i;   //Integer i
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo 
void setup()
{

  myservo.attach(9); // servo library
  pinMode(6,INPUT); //IR sensor
  Serial.begin(9600); 
}

void loop()
{
int door= digitalRead(6); //Read signal from IR sensor
Serial.print("door: ");
Serial.println(door);
  if (door==0)     // if IR sensor detects a person
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees - door is open
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);           
    }  
    delay(5000);   // door is kept open for 5 seconds
 for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
    // in steps of 1 degree // door is closed
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);
    }  pos = 0; }
