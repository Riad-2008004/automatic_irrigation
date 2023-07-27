#include <Servo.h>
Servo myservo;
Servo pumpservo;



int east;
int west;
int error;

int servoposition=90;

int ground_1;
int ground_2;

int pump = 10;

void setup() 
{
  Serial.begin(9600);
  pinMode(pump,OUTPUT);
  
  myservo.attach(9);
  pumpservo.attach(6);

  myservo.write(servoposition);
  delay(100);

  pumpservo.write(servoposition);
  delay(100);

  digitalWrite(pump,LOW);
  
}

void loop()
{
  east=analogRead(A1);
  west=analogRead(A2);

  ground_1=analogRead(A3);
  ground_2=analogRead(A4);

  error=east-west;

  if(error>25)
  {
    if(servoposition<=150)
    {
      servoposition++;
      myservo.write(servoposition);
      delay(80);
    }
  }

  else if (error<-25)
  {
    if(servoposition>20)
    {
      servoposition--;
      myservo.write(servoposition);
      delay(80);
    }
  }
  else if (ground_2>=868)
  {
    pumpservo.write(5);
    delay(2000);
    digitalWrite(pump,HIGH);
    Serial.println("PUMP 2 ON ");
    Serial.println(ground_2);
    delay(100);
  }
  
  else if(ground_1>=868)
  {
    pumpservo.write(175);
    delay(2000);
    digitalWrite(pump,HIGH);
    Serial.println("PUMP 1 ON ");
    Serial.println(ground_1);
    delay(100);
  }
  else
  {
    pumpservo.write(90);
    digitalWrite(pump,LOW);
    Serial.println("ERROR");
  }

}
