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


Motor left_motor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Motor right_motor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);


void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
}

void loop() {

  int left = !digitalRead(2);
  int right = !digitalRead(3);
  

  if(!left  && right){
    right_motor.drive(200,20);
    right_motor.brake();
  }
  else if(left && !right){
    left_motor.drive(200,20);
    left_motor.brake();
  }
  else{
    forward(left_motor, right_motor, 200);
    delay(5);
  }

  

  brake(left_motor,right_motor);
}