#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_SMS_SHIELD
#define INCLUDE_VIBRATION_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD

/* Include 1Sheeld library.*/
#include <OneSheeld.h>
#include <string.h>


/* Define a boolean flag. */
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
  /* Start communication.*/
  Serial.begin(9600);
  OneSheeld.begin();
  PushButton.setOnButtonStatusChange(&Emergency);
}

void loop()
{ 
  
}


void Emergency(byte isButtonPressed) {

      /* Send SMS. */
      if(isButtonPressed)
      {  
        if(!isMessageSent)
        lat = GPS.getLatitude();
        lon = GPS.getLongitude();
        Message1 = String(lat,8);
        Message2 = String(lon,8);
     
        Message = "I need Help! Google Maps - https://www.google.co.in/maps/place/" + Message1 + "," + Message2;
        Serial.println(Message);
     
        SMS.send("0819033655",Message);
        isMessageSent = true;
      }
      else{
        isMessageSent = false;
      }
}
