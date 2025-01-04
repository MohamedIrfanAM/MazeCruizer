#include <SparkFun_TB6612.h>

#define AIN1 9
#define BIN1 7
#define AIN2 10
#define BIN2 6
#define PWMA 11
#define PWMB 5
#define STBY 8

const int offsetA = -1;
const int offsetB = 1;

#define ENCODER1 12 //right c1
#define ENCODER2 2  // right c2
#define ENCODER3 3  // left c2
#define ENCODER4 4  // left c1

volatile long int right_encoder_pos = 0;
volatile long int left_encoder_pos = 0;
long int right_last_encoder_pos = 0;
long int left_last_encoder_pos = 0;
long int last_millis = 0;


void left_encoder()
{
  if (digitalRead(ENCODER4) == HIGH)
  {
    left_encoder_pos++;
  }
  else
  {
    left_encoder_pos--;
  }
}
void right_encoder()
{
  if (digitalRead(ENCODER1) == HIGH)
  {
    right_encoder_pos--;
  }
  else
  {
    right_encoder_pos++;
  }
}

Motor left_motor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Motor right_motor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup()
{

  Serial.begin(9600);
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
  pinMode(ENCODER3, INPUT_PULLUP);
  pinMode(ENCODER4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER2), right_encoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER3), left_encoder, RISING);
}


void loop()
{
  //  Use of the drive function which takes as arguements the speed
  //  and optional duration.  A negative speed will cause it to go
  //  backwards.  Speed can be from -255 to 255.  Also use of the 
  //  brake function which takes no arguements.
  //  left_motor.drive(255,1000);
  //  left_motor.drive(-255,1000);
  //  left_motor.brake();
  //  delay(1000);
   
  //  Use of the drive function which takes as arguements the speed
  //  and optional duration.  A negative speed will cause it to go
  //  backwards.  Speed can be from -255 to 255.  Also use of the 
  //  brake function which takes no arguements.

  //  right_motor.drive(-255,1000);
  //  right_motor.brake();
  //  delay(1000);
   
  //  Use of the forward function, which takes as arguements two motors
  //  and optionally a speed.  If a negative number is used for speed
  //  it will go backwards
  //  forward(left_motor, right_motor, 255);
  //  delay(1000);
   
  //  Use of the back function, which takes as arguments two motors 
  //  and optionally a speed.  Either a positive number or a negative
  //  number for speed will cause it to go backwards
  //  back(left_motor, right_motor, 255);
  //  delay(1000);
   
  //  Use of the brake function which takes as arguments two motors.
  //  Note that functions do not stop motors on their ow n.
  //  brake(left_motor, right_motor);
  //  delay(1000);
   
  //  //Use of the left and right functions which take as arguements two
  //  //motors and a speed.  This function turns both motors to move in 
  //  //the appropriate direction.  For turning a single motor use drive.
  //  left(left_motor, right_motor, 255);
  //  delay(1000);
  //  right(left_motor, right_motor, 255);
  //  delay(1000);
   
   //Use of brake again.
  //  brake(left_motor, right_motor);
  //  delay(1000);

  int right_rpm_speed = (((float)right_encoder_pos - (float)right_last_encoder_pos) / 700) * 60.0 * (1000 / (millis() - last_millis));
  int left_rpm_speed = (((float)left_encoder_pos - (float)left_last_encoder_pos) / 700) * 60.0 * (1000 / (millis() - last_millis));
  right_last_encoder_pos = right_encoder_pos;
  left_last_encoder_pos = left_encoder_pos;
  last_millis = millis();
  // Position
  Serial.print("Left motor encoder: ");
  Serial.print(left_encoder_pos);
  Serial.print("\tRight motor encoder: ");
  Serial.println(right_encoder_pos);
  //Speed
  // Serial.print("Left motor Speed: ");
  // Serial.print(left_rpm_speed);
  // Serial.print("\tRight motor Speed: ");
  // Serial.println(right_rpm_speed);
  delay(100);
}
