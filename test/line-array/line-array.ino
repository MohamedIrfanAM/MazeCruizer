void setup() {
  Serial.begin(9600);
}

void loop() {
 
  int sensorValues[5];
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(A0 + i);
  }


  Serial.print("Sensor Values: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    if (i < 4) {
      Serial.print(", "); 
    }
  }
  Serial.println();


  delay(100);
}
