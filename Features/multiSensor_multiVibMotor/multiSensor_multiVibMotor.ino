// Define Pins for Sensor 1 
#define trigPin1 4
#define echoPin1 5

//Define Pins for Sensor 2
#define trigPin2 6
#define echoPin2 7

// Define Pins for VibMotor 1
#define motorPin1 12

// Define Pins for VibMotor 2
#define motorPin2 13

long duration, distance, UltraSensor, UltraSensorTwo;


void setup()
{ 
  Serial.begin(9600); // to use the serial monitor.
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
 
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

void loop()
{ 
  SonarSensor(trigPin1, echoPin1);
  UltraSensor = distance;

  SonarSensor(trigPin2, echoPin2);
  UltraSensorTwo = distance;

  Serial.print("Sensor1-");
  Serial.print(UltraSensor); // print out the distance from Sensor One on Serial Monitor
  Serial.println("cm");

  Serial.print("Sensor2-");
  Serial.print(UltraSensorTwo); // print out the distance from Sensor Two on Serial Monitor
  Serial.println("cm");

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
