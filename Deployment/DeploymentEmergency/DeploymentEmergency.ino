  #define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_SMS_SHIELD
#define INCLUDE_VIBRATION_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_MIC_SHIELD

/* Include 1Sheeld library.*/
#include <OneSheeld.h>
#include <string.h>

// Define Pins for Sensor 1
#define trigPin1 4
#define echoPin1 5

//Define Pins for Sensor 2
#define trigPin2 6
#define echoPin2 7

// Define Pin for VibMotor 1
#define motorPin1 12

// Define Pin for VibMotor 2
#define motorPin2 13

/* Define a boolean flag. */
long UltraSensor, UltraSensorTwo;
unsigned long previousMillis = 0;
unsigned long interval = 250;

unsigned long previousMillisAlarm = 0;
unsigned long intervalAlarm = 3000;
boolean alarmReset = false;

float lat;
float lon;
String Message;
String Message1;
String Message2;
char latitude[10];
char longitude[10];


void setup()
{
  /* Start communication.*/
  OneSheeld.begin();

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

long SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;
  return distance;
}

void triggerSensor(int motorPin, long lSensorDistInCm, long lMaxDistInCm, char* sMsg)
{
  int iTimeToDelayInMs = 100 * (lMaxDistInCm / lSensorDistInCm) * (lMaxDistInCm / lSensorDistInCm); // 60 cm -- 50 ms, 30 cm -- 200 ms
  if (iTimeToDelayInMs > 1000) iTimeToDelayInMs = 1000;

  if (lSensorDistInCm <= lMaxDistInCm) // cm
  {
    digitalWrite(motorPin, HIGH); // motor on
    delay(iTimeToDelayInMs);
    digitalWrite(motorPin, LOW); // motor off
    delay(iTimeToDelayInMs);
  }
  else
  {
    digitalWrite(motorPin, LOW);
  }
  //  Terminal.print(sMsg);
  //  Terminal.print(lDist);
  //  Terminal.print("cm, delay: ");
  //  Terminal.print(iTimeToDelayInMs);
  //  Terminal.println("ms.");
}

void SensorHandler() {

  long lSensorDist1InCm = SonarSensor(trigPin1, echoPin1);
  long lMaxDistInCm = 60;
  triggerSensor(motorPin1, lSensorDist1InCm, lMaxDistInCm, "Sensor1: ");

  long lSensorDist2InCm = SonarSensor(trigPin2, echoPin2);
  lMaxDistInCm = 100;
  triggerSensor(motorPin2, lSensorDist2InCm, lMaxDistInCm, "Sensor2: ");
}

void Alarm() {
  int ledPin = 8;
  int piezoPin = 8;
  unsigned long currentMillisAlarm = millis();

  if (currentMillisAlarm - previousMillisAlarm > intervalAlarm)
  {
    previousMillisAlarm = currentMillisAlarm;

    if (OneSheeld.isAppConnected())
    {
      if(true)
      {
      digitalWrite(ledPin, LOW);
      //tone(piezoPin, 0, 0);
      alarmReset = true;
      }
    }
    else {
      digitalWrite(ledPin, HIGH);
      tone(piezoPin, 12500, 500);
      delay(1000);
      alarmReset = false;
    }
  }
}
 void loop()
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
      previousMillis = currentMillis;
      SensorHandler();
    }
    if (PushButton.isPressed())
    {
      Terminal.println("Button Pressed");
      lat = GPS.getLatitude();
      lon = GPS.getLongitude();
      Message1 = String(lat, 8);
      Message2 = String(lon, 8);

      Message = "I need Help! Google Maps - https://www.google.co.in/maps/place/" + Message1 + "," + Message2;
      Terminal.print("Message Sent");

      SMS.send("0846371854", Message);
    }

    Alarm();
  }
