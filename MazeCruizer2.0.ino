// Arduino pins
#define leftMotor1 5
#define leftMotor2 4
#define leftMotorEnable 6
#define rightMotor1 2
#define rightMotor2 3
#define rightMotorEnable 9
#define leftEcho 11 
#define leftTrig 10
#define rightEcho 13
#define rightTrig 12
#define frontEcho 8
#define frontTrig 7 

// Bot movements
void stop()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
}
void forward()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(800);
  stop();
}
void dforward()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(500);
  stop();
}
void right()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  delay(700);
  stop();
}
void dright()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  delay(120);
  stop();
}
void left()
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(700);
  stop();
}
void dleft()
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(120);
  stop();
}

// Obstacle detection
void ping(int trig)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
}
double distance(int echo)
{
  double duration = pulseIn(echo, HIGH);
  double distance = duration/29/2;
  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(leftMotor1,OUTPUT);
  pinMode(leftMotor2,OUTPUT);
  pinMode(rightMotor1,OUTPUT);
  pinMode(rightMotor1,OUTPUT);
  pinMode(leftTrig,OUTPUT);
  pinMode(rightTrig,OUTPUT);
  pinMode(frontTrig,OUTPUT);
  pinMode(leftEcho,INPUT);
  pinMode(rightEcho,INPUT);
  pinMode(frontEcho,INPUT);
  pinMode(leftMotorEnable,OUTPUT);
  pinMode(rightMotorEnable,OUTPUT);
  // junction();
  digitalWrite(leftMotorEnable,HIGH);
  analogWrite(rightMotorEnable,218);

}

void loop() {
  
  ping(frontTrig);
  long frontDist = distance(frontEcho);
  ping(rightTrig);
  long rightDist = distance(rightEcho);
  ping(leftTrig);
  long leftDist = distance(leftEcho);

  Serial.println("left: ");
  Serial.println(leftDist);

  Serial.println("right: ");
  Serial.println(rightDist);

  Serial.println("front: ");
  Serial.println(frontDist);
  Serial.print("\n");
  Serial.print("\n");

  if(rightDist > 40)
  {
    stop();
    delay(100);
    dforward();
    delay(100);
    right();
    delay(100);
    dforward();
  }
  else if(frontDist > 10)
  {
    if(frontDist > 28)
    {
      if(leftDist < 5)
      {
        dright();
      }
      else if(rightDist < 5)
      {
        dleft();
      }
      // if(leftDist > rightDist)
      // {
      //   dleft();
      // }
      // else if(rightDist > leftDist)
      // {
      //   dright();
      // }
    }
    forward();
  }
  else if(frontDist <= 10 && leftDist > 6)
  {
    stop();
    delay(100);
    left();
    delay(100);
  }
  else if(frontDist <= 10 && rightDist > 6)
  {
    stop();
    delay(100);
    right();
    delay(100);
  }
  else if(frontDist <= 10 && (leftDist < 6 || rightDist < 6))
  {
      stop();
      delay(100);
      left();
      delay(100);
      left(); 
      delay(100);
  }
}
