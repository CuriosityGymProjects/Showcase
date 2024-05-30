#include <U8glib.h>   // Include Library 
const int trigPin=12;    //Trigpin of Ultrasonic sensor is connected
const int echoPin=13;  //echopin of Ultrasonic sensor is connected
const int reference=192.024;  //Ultrasonic sensor is need to mounted at this height
const int buzzer=8;  //Buzzer is connected

unsigned long previousMillis = 0;
const long interval = 1000;
int led=7;   // LED is connected

double feet;         //Adding Variable feet
int feet_only;       //Adding Variable integer feet
double dec;         //Adding Variable decimal place
int inches_only;  //Adding Variable integer inches
long duration;     //Adding Variable to do mathematical operation to get distance
int distance;        //Adding Variable to get distance
int height;           //Adding Variable to get height

long duration2; // Adding Variable duration2
int distance2; // Adding Variable distance2
int height2; // Adding Variable to height2

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
   
void setup() {
  u8g.setFont(u8g_font_fub49n);   //Font type
  u8g.setColorIndex(1);                 //Colour index to set colour                  
  pinMode(trigPin,OUTPUT);        //Ultrasonic sensor Trigpin as output
  pinMode(echoPin,INPUT);         //Ultrasonic sensor echo as input
  Serial.begin(9600);                    //For serial monitor
  pinMode(12,OUTPUT);             //Make Arduino digital pin 12 as output
}
void loop() {
  digitalWrite(trigPin,LOW);  //Make trigpin low for delay microseconds 2
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH); //Make trigpin high for delay microseconds 10
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);   //Make trigpin low
  duration=pulseIn(echoPin,HIGH);  //echo pin high and store value in duration 
  distance=duration*0.034/2;            //Do mathematical operation and store 
                                                            value in variable distance
  height=reference-distance;            // Getting the value of height
 
  //Serial.println("Height");  //For testing on serial monitor in actual programming 
                                              it need to be hided
  //Serial.println(height);
  //delay(2000);
  digitalWrite(trigPin,HIGH);  //Make Trigpin High for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW); //Make Trigpin Low for 10 microseconds

  duration2=pulseIn(echoPin,HIGH); //echo pin high and store value in duration2 
  distance2=duration2*0.034/2; //Do mathematical operation and store 
                                                            value in variable distance2
  height2=reference-distance2;  // Getting the value of height2
  Serial.println("Distance:");//For testing on serial monitor in actual programming 
                                              it need to be hided
  Serial.println(distance);
  delay(3000);
  if(distance<156){ // when distance is less than 156
  if(height==height2){ // check height and height2 values are same

   tone(buzzer,1000); // for 1 second buzzer will make sound 
      delay(1000);
   noTone(buzzer); // buzzer will stop making sound for a delay for 1sec
      delay(1000);
    double feet=height*0.0328084; 
               //Adding Variable feet converting the height in cm to inches
  int feet_only=feet; // Adding variable value in feet
  double dec=(feet-feet_only)*12; //Adding variable dec and converting 
                                                        value in inches to feet    
  int inches_only =dec; // Adding variable value in dec

 u8g.firstPage();  
  do {
    u8g.setPrintPos(0,55);   //Printing the value on x-axis=0 and y-axis=55
    u8g.print(feet_only);         //Displaying Variable value on OLED display

    if(inches_only<10){        

    int a=0; Adding variable a and put the value 0
    u8g.setPrintPos(55,55); //Printing the value on x-axis=55 and y-axis=55
    u8g.print(a); //Displaying Variable value on OLED display
    u8g.setPrintPos(90,55); //Printing the value on x-axis=90 and y-axis=55
    u8g.print(inches_only);   //Displaying Variable value on OLED display
    }
else{
      u8g.setPrintPos(57,55);  //Printing the value on x-axis=0 and y-axis=55
    u8g.print(inches_only);      //Printing variable value OLED display
    }
  } while( u8g.nextPage() );
  Serial.print(feet_only);        //Printing Feet value
  Serial.print(" ");
  Serial.print(inches_only);    //Printing Inch value
  Serial.println();
  delay(3000);                       //for 3 seconds
   }}
else
{
unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    for(;;){
    u8g.sleepOn();    //OLED will go for sleep

    digitalWrite(led,HIGH); //Make LED high for delay 1 second 
    delay(1000);
    digitalWrite(led,LOW); //Make LED low for delay 1 second
    delay(1000);

    digitalWrite(trigPin,LOW); // Make trigpin low for delay microseconds 2
  delayMicroseconds(2);

 digitalWrite(trigPin,HIGH); // Make trigpin high for delay microseconds 10
  delayMicroseconds(10);    
  digitalWrite(trigPin,LOW);  // Make trigpin low 

  duration=pulseIn(echoPin,HIGH); // echo pinmode high storing value in                        
                                                             duration
  distance=duration*0.034/2; // ultrasonic distance formula
   
    if(distance<156){
      u8g.sleepOff(); ////OLED will be on
      break;
    }
    }
  }
  }
}
