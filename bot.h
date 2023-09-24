#include <Arduino.h>
#ifndef Bot_h
#define Bot_h

class Bot
{
private:
  // Motor
  int leftMotor1 = 5;
  int leftMotor2 = 6;
  int leftMotorEn = 10;
  int leftMotorSpeed = 100;
  int leftMotorCount = 0;
  int rightMotor1 = 4;
  int rightMotor2 = 3;
  int rightMotorEn = 11;
  int rightMotorSpeed = 100;
  int rightMotorCount = 0;
  // Sensor
  int frontIr = 7;
  int leftIr = 12;
  int rightIr = 8;

public:
  void initialize();
  void stop();
  void forward();
  void right(int d);
  void left(int d);
  bool rightWall();
  bool leftWall();
  bool frontWall();
};

#endif