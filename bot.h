#include <Arduino.h>
#ifndef Bot_h
#define Bot_h

class Bot
{
private:
  // Motor and encoders
  int leftMotor1 = 5;
  int leftMotor2 = 4;
  int leftMotorEn = 3;
  int leftEncoder1 = 12;
  int leftEncoder2 = 13;
  int leftMotorSpeed = 155;
  int leftMotorCount = 0;
  int rightMotor1 = 8;
  int rightMotor2 = 7;
  int rightMotorEn = 6;
  int rightEncoder1 = 14;
  int rightEncoder2 = 15;
  int rightMotorSpeed = 155;
  int rightMotorCount = 0;
  // Sensor
  int frontIr = 11;
  int leftIr = 0;
  int rightIr = 1;

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