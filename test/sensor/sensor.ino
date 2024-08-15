int frontir = 11; // connect ir sensor to arduino pin 3
int rightir = 1;
int leftir = 0;

void setup() 
 {
  pinMode (frontir, INPUT); // sensor pin INPUT
  pinMode (rightir , INPUT); // sensor pin INPUT
  pinMode (leftir, INPUT); // sensor pin INPUT

  Serial.begin (9600); // Starts the serial communication
 }

void loop()
 {
  //Define a variables for read the IRsensor   
  int front = digitalRead(frontir); 
  int left = digitalRead (leftir); 
  int right = digitalRead(rightir);
  
  // Prints the output data on the Serial Monitor 
  Serial.print("Front:");
  Serial.println(front);
  Serial.print("left:");
  Serial.println(left);
  Serial.print("right:");
  Serial.println(right);
  delay(200);
 }