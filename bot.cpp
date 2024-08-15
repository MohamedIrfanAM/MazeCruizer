#include "bot.h"

void Bot::initialize()
{
  // Serial Communication
  Serial.begin(9600);

  // Motor I/O pins
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorEn, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorEn, OUTPUT);

  // Default States
  digitalWrite(leftMotorEn, HIGH);
  digitalWrite(rightMotorEn, HIGH);
  analogWriteFreq(500000);
  analogWriteResolution(8);
  analogWrite(leftMotorEn, leftMotorSpeed);
  analogWrite(rightMotorEn, rightMotorSpeed);

  // Sensor I/O pins
  pinMode(frontIr, INPUT);
  pinMode(leftIr, INPUT);
  pinMode(rightIr, INPUT);
}

void Bot::forward()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
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