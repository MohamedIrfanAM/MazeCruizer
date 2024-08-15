void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
  analogWriteFreq(500000);
  analogWriteResolution(8);
  
}

void loop() { 
 digitalWrite(5,LOW);
 digitalWrite(3,HIGH);
  // analogWrite( 3,255);
  digitalWrite(4,HIGH);
  // analogWrite( 6,150);
  digitalWrite(6,HIGH);
 digitalWrite(7,LOW);
 digitalWrite(8,HIGH);
  // digitalWrite(7,HIGH);


}
