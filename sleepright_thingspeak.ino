#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ThingSpeak.h> // Include the ThingSpeak library
#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library

Adafruit_MPU6050 mpu;
int count = 0;
char thingSpeakApiKey[] = "BWMVH1IEKWJ3SYOU"; // Replace with your ThingSpeak API key
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 10000; // Update every 10 seconds

WiFiClient client; // Declare a WiFiClient object
const char* wifi_ssid = "Hello"; // Replace with your WiFi SSID
const char* wifi_password = "robotics4321"; // Replace with your WiFi password
const unsigned long channelID = 2337976; // Replace with your ThingSpeak channel ID

void setup(void)
{
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D5, OUTPUT);
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Set up motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);  // Keep it latched. Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  // Connect to WiFi
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client); // Initialize ThingSpeak client

  Serial.println("");
  delay(100);
}

void loop()
{
  if (mpu.getMotionInterruptStatus())
  {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("AccelX:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(a.acceleration.z);

    if (a.acceleration.x < -2 || a.acceleration.y < 0 || a.acceleration.z < 0)
    {
      digitalWrite(D5, HIGH);  // Turn on the LED
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("LED HIGH");  // Print the LED state
      count = count + 1;
      delay(1000);  // Wait for 1 second
      Serial.print("Count: ");
      Serial.println(count);
    }
    else
    {
      digitalWrite(D5, LOW);  // Turn off the LED
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("LED LOW");  // Print the LED state
    }

    // Send data to ThingSpeak every updateInterval
    if (millis() - lastUpdateTime >= updateInterval)
    {
      lastUpdateTime = millis();

      // Update ThingSpeak fields
      ThingSpeak.setField(1, a.acceleration.x);
      ThingSpeak.setField(2, a.acceleration.y);
      ThingSpeak.setField(3, a.acceleration.z);

      if (ThingSpeak.writeFields(channelID, thingSpeakApiKey))
      {
        Serial.println("Data sent to ThingSpeak");
      }
      else
      {
        Serial.println("Failed to send data to ThingSpeak");
      }
    }
  }

  delay(10);
}
