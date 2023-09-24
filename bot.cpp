#include "bot.h"

void Bot::initialize()
{
  Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorEn, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorEn, OUTPUT);
  analogWrite(leftMotorEn, leftMotorSpeed);
  analogWrite(rightMotorEn, rightMotorSpeed);
  pinMode(frontIr, INPUT);
  pinMode(leftIr, INPUT);
  pinMode(rightIr, INPUT);
}

void Bot::forward()
{
  Serial.println(digitalRead(rightIr));
  int d = 0;
  while (d < 10)
  {
    d++;
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(25);
    // if (rightWall())
    // {
    //   Serial.println("Right Wall while going forward");
    //   left(80);
    // }
    // else if (leftWall())
    // {
    //   Serial.println("Left Wall while going forward");
    //   right(80);
    // }
    // else if (frontWall())
    // {
    //   Serial.println("Front Wall while going forward");
    //   stop();
    //   break;
    // }
  }
  stop();
}

void Bot::stop()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void Bot::right(int d)
{
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  delay(d);
  stop();
}

void Bot::left(int d)
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  delay(d);
  stop();
}

bool Bot::rightWall()
{
  Serial.println("Right Wall");
  return digitalRead(rightIr) == LOW;
}

bool Bot::leftWall()
{
  return digitalRead(leftIr) == LOW;
}

bool Bot::frontWall()
{
  return digitalRead(frontIr) == LOW;
}