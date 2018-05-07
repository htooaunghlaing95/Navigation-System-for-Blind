//Define the Used Shield
#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_SMS_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD

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

// Define Pin for PushButton
#define pushButton 8

long duration, distance, UltraSensor, UltraSensorTwo;
boolean isMessageSent = false;
float lat;
float lon;
String Message;
String Message1;
String Message2;
char latitude[10];
char longitude[10];


void setup()
{ 
  OneSheeld.begin();
  Serial.begin(9600); // to use the serial monitor.
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  pinMode(pushButton, INPUT);

  //PushButton.setOnButtonStatusChange(&Emergency);
}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  //delay(100);
}

void SensorHandler() {

  SonarSensor(trigPin1, echoPin1);
  UltraSensor = distance;

  SonarSensor(trigPin2, echoPin2);
  UltraSensorTwo = distance;

  if (UltraSensor <= 60 && UltraSensor >= 45) // Checking the distance, you can change the value
  {
    digitalWrite(motorPin1, HIGH); // motor on
    delay(200);
    digitalWrite(motorPin1, LOW); // motor off
    delay(200);
  } 
  else if(UltraSensor < 45 && UltraSensor >=30)
  {
    digitalWrite(motorPin1, HIGH); // when greater than 100cm
    delay(100);
    digitalWrite(motorPin1, LOW);
    delay(100);
  } 
  else if(UltraSensor < 30) 
  {
   digitalWrite(motorPin1, HIGH);
   delay(50);
   digitalWrite(motorPin1, LOW);
   delay(50); 
  }
  else
  {
    digitalWrite(motorPin1, LOW);
  }

    // For VibMotor Two

  if (UltraSensorTwo <= 60 && UltraSensorTwo >= 45) // Checking the distance, you can change the value
  {
    digitalWrite(motorPin2, HIGH); // motor on
    delay(200);
    digitalWrite(motorPin2, LOW); // motor off
    delay(200);
  } 
  else if(UltraSensorTwo < 45 && UltraSensorTwo >=30)
  {
    digitalWrite(motorPin2, HIGH); // when greater than 100cm
    delay(100);
    digitalWrite(motorPin2, LOW);
    delay(100);
  } 
  else if(UltraSensorTwo < 30) 
  {
   digitalWrite(motorPin2, HIGH);
   delay(50);
   digitalWrite(motorPin2, LOW);
   delay(50); 
  }
  else
  {
    digitalWrite(motorPin2, LOW);
  }
}                                                                          

void loop()
{ 
  SensorHandler(); // Obstacle Detection Feature

  // Implement the Emergency button feature 
  
    if(PushButton.isPressed())
        {  
          lat = GPS.getLatitude();
          lon = GPS.getLongitude();
          Message1 = String(lat,8);
          Message2 = String(lon,8);
       
          Message = "I need Help! Google Maps - https://www.google.co.in/maps/place/" + Message1 + "," + Message2;
          Serial.println(Message);
       
          SMS.send("0877175292",Message);
          delay(3000);
         }
      delay(500);
}
