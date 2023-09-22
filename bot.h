#include <Arduino.h>
#ifndef Bot_h
#define Bot_h

class Bot
{
private:
  int leftMotor1;
  int leftMotor2;
  int leftMotorEn;
  int leftMotorSpeed;
  int leftMotorCount;
  int rightMotor1;
  int rightMotor2;
  int rightMotorEn;
  int rightMotorSpeed;
  int rightMotorCount;

public:
  void initialize();
  void stop();
  void forward();
  void right();
  void left();
};

#endif