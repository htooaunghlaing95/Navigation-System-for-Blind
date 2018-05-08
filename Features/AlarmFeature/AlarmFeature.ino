//#define CUSTOM_SETTINGS
//#define INCLUDE_BUZZER_SHIELD

#include <OneSheeld.h>
//#include <String.h>  
int ledPin = 8;
int piezoPin = 8;

void setup()
{
  OneSheeld.begin();
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if(OneSheeld.isAppConnected())
  {
    digitalWrite(ledPin, LOW);
    tone(piezoPin, 0, 0);
  }
  else{
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, 10000, 500);
    delay(1000);
  }
}

