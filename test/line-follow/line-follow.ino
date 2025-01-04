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



void setup() {
  Serial.begin(9600);
}

void loop() {
 
  int sensorValues[5];
  for (int i = 0; i < 5; i++) {
    sensorValues[5-i-1] = (analogRead(A0 + i) > 500 ? 0 : 1);
    // sensorValues[5-i-1] = analogRead(A0 + i);
  }



  

  if(sensorValues[1] && !sensorValues[3]){
    right_motor.drive(255,30);
    right_motor.brake();
  }
  else if(!sensorValues[1] && sensorValues[3]){
    left_motor.drive(255,30);
    left_motor.brake();
  }
  else{
    forward(left_motor, right_motor, 255);
    delay(300);
  }

  


  // Serial.print("Sensor Values: ");
  // for (int i = 0; i < 5; i++) {
  //   Serial.print(sensorValues[i]);
  //   if (i < 4) {
  //     Serial.print(", "); 
  //   }
  // }
  // Serial.println();



  brake(left_motor,right_motor);
}
