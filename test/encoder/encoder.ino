#include <Arduino.h>
#include <PIDController.h>
#define ENCODER1 12
#define ENCODER2 13
#define ENCODER3 14
#define ENCODER4 15

volatile long int right_encoder_pos = 0;
volatile long int left_encoder_pos = 0;
long int right_last_encoder_pos = 0;
long int left_last_encoder_pos = 0;
long int last_millis = 0;
int right_power = 255;
int left_power = 255;
int mazedistance = 180; // in mm
int mazedistanceEncoderCount = mazedistance * 5.0640;

float Setpoint, Input, Output;
float Kp = 0, Ki = 5, Kd = 0;
PIDController angle;
PIDController distance_pid;

void left_encoder()
{
  if (digitalRead(ENCODER2) == HIGH)
  {
    left_encoder_pos--;
  }
  else
  {
    left_encoder_pos++;
  }
}
void right_encoder()
{
  if (digitalRead(ENCODER4) == HIGH)
  {
    right_encoder_pos++;
  }
  else
  {
    right_encoder_pos--;
  }
}

void moveForward()
{
  int t = right_encoder_pos + mazedistanceEncoderCount;
  while (right_encoder_pos < t)
  {
    int power = distance_pid.compute(right_encoder_pos - t);
    Serial.println(power);
    analogWrite(3, power);
    analogWrite(6, power);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    delay(20);
  }
  analogWrite(3, 0);
  analogWrite(6, 0);
}

void setup()
{
  Serial.begin(9600);
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
  pinMode(ENCODER3, INPUT_PULLUP);
  pinMode(ENCODER4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER1), left_encoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER3), right_encoder, RISING);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  analogWriteFreq(500000);
  analogWriteResolution(16);

  angle.begin();
  angle.tune(15, 0, 0);
  angle.limit(-100, 100);
  angle.setpoint(0);

  distance_pid.begin();
  distance_pid.tune(660, 0, 100);
  distance_pid.limit(-65535, 65535);
}

void loop()
{
  int right_rpm_speed = (((float)right_encoder_pos - (float)right_last_encoder_pos) / 700) * 60.0 * (1000 / (millis() - last_millis));
  int left_rpm_speed = (((float)left_encoder_pos - (float)left_last_encoder_pos) / 700) * 60.0 * (1000 / (millis() - last_millis));
  right_last_encoder_pos = right_encoder_pos;
  left_last_encoder_pos = left_encoder_pos;
  last_millis = millis();
  Serial.println(right_encoder_pos);
  Serial.println(left_encoder_pos);
  int powerdiff = angle.compute(right_rpm_speed - left_rpm_speed);
  moveForward();
  delay(10000);
  // Serial.println(speed);
  //   Serial.println(powerdiff);
  //   digitalWrite(5,LOW );
  // //  digitalWrite(3,HIGH);
  //   analogWrite( 3,65535);
  //   digitalWrite(4,HIGH);
  //   analogWrite( 6,65535);
  // //   // digitalWrite(6,LOW);
  //  digitalWrite(7,LOW);
  //  digitalWrite(8,HIGH);
  //   // digitalWrite(7,HIGH);
  delay(100);
}