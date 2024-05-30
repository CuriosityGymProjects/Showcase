#include <ESP8266WiFi.h>  
#include "AdafruitIO_WiFi.h"  //Include Adafruit IO Library
int parking_count = 0;  //Initialize Parking counter
int Distance_value = 0;  //Initialize distance value
const char* wifi_ssid = "Curiosity Gym";  
const char* wifi_password = "robotics4321";
#define IO_USERNAME "anita4dk"  //mention your IO username
#define IO_KEY "aio_KfDD76rmBfNEhLlJHShkofYPfL4f" // mention your IO key
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, wifi_ssid, wifi_password); 
// Initialize Adafruit IO connection with the credentials provided
AdafruitIO_Feed *feed_1 = io.feed("Parking 1");
// Set feed1 to Parking Slot no. 1
AdafruitIO_Feed *feed_2 = io.feed("Parking 2");
// Set feed2 to Parking Slot no. 2
AdafruitIO_Feed *feed_3 = io.feed("Parking 3");
// Set feed3  to Parking Slot no. 3
AdafruitIO_Feed *feed_4 = io.feed("Parking 4");
WiFiClient client;  // Initialize New WifiClient object

int measure_distance()  //Function to fetch the distance between the Ultrasonic sensor and the object
{
digitalWrite(D4, LOW);  
delayMicroseconds(2);
digitalWrite(D4, HIGH);
delayMicroseconds(10);
digitalWrite(D4, LOW);
long duration = pulseIn(D0, HIGH);
int cm = duration / 29 / 2;
return cm;
}
void setup()
{
  parking_count = 0;  
  Distance_value = 0;
Serial.begin(115200);   // Serial Begin
WiFi.begin(wifi_ssid, wifi_password);  // begin the WIFI Connection
int i=0;
  

while (WiFi.status() != WL_CONNECTED && i<50) { //Check whether WIFI connected
    delay(500);
    Serial.println(".");
  }
pinMode(D1, OUTPUT);  //Set D1 and D2 as output
 pinMode(D2, OUTPUT);
 if(WiFi.status() != WL_CONNECTED){  
// Indicate on onboard LED if wifi isn’t connected
  digitalWrite(D1, HIGH);
  delay(3000);
  digitalWrite(D1, LOW);
  }
 if(WiFi.status() == WL_CONNECTED){  
//If WIfi connected indicate green color on onboard LED
   digitalWrite(D2, HIGH);
   delay(3000);
   digitalWrite(D2, LOW);
  }

 io.connect();  //Connect to the IO Dashboard of Adafruit
 pinMode(D4, OUTPUT); // Receiver Terminal of Ultrasonic
 pinMode(D0, INPUT);  // Transmit terminal of Ultrasonic
  pinMode(D8, INPUT);  // Push Button inputs

}
void loop()
{
  // io.run(); is required for all sketches
   // it should always be present at the top of your loop
   // function. it keeps the client connected to
   // io.adafruit.com, and processes any incoming data.
   io.run();
  Distance_value = (measure_distance()); 
        Serial.println(Distance_value);
 
// Call the distance calculation function and store the return value in distance value
  if (digitalRead(D8) == HIGH) {  //Check if Push button pressed
    if (parking_count == 0) {  //If Parking value is 0 update Parking slot no. 1 value
      Serial.println("Updating ");


      Serial.println((parking_count + 1));
      Serial.println("Slot");
      feed_1 -> save(float(Distance_value),0, 0, 2); //Write to Feed1
      Serial.println("Waiting ");
       Serial.print(1);
       Serial.println("seconds");
for (int i = 0; i <1*60 ; i++)
       {
       delay(1000);
      }
}

if (parking_count == 1) {  
 //If Parking value is 1 update Parking slot no. 2 value

      Serial.println("Updating ");
      Serial.print((parking_count + 1));
      Serial.println("Slot");
      feed_2 -> save(float(Distance_value),0, 0, 2);


      Serial.print("Waiting ");
       Serial.print(1);
       Serial.println("seconds");

       for (int i = 0; i <1*60 ; i++)
       {
       delay(1000);
      }

    }
if (parking_count == 2) {         //If Parking value is 2 update Parking slot no. 3 value
     Serial.println("Updating ");
      Serial.print((parking_count + 1));
      Serial.println("Slot");
      feed_3 -> save(float(Distance_value),0, 0, 2);
      Serial.print("Waiting ");
      Serial.print(1);
      Serial.println("seconds");

       for (int i = 0; i <1*60 ; i++)
       {
       delay(1000);
      }

    }
if (parking_count == 3) {   //If Parking value is 3 update Parking slot no. 4 value

      Serial.println("Updating ");
      Serial.print((parking_count + 1));
      Serial.println("Slot");
      feed_4 -> save(float(Distance_value),0, 0, 2);
      Serial.print("Waiting ");
       Serial.print(1);
       Serial.println("seconds");

      

 for (int i = 0; i <1*60 ; i++)
       {
       delay(1000);
      }

    }
    parking_count = parking_count + 1;  
// After updating particular slot,  increment the parking counter
}

if (parking_count > 3) {
// Reset the Parking count if greater than 3
    parking_count = 0;
    Serial.println("Parking slot resetted");

  }

}
