  
  #define R1 12
  int relState = LOW;
  
  void setup() {
    pinMode(R1, OUTPUT);
  }
  
  void loop() {
    digitalWrite(R1, HIGH);
    delay(250);
    digitalWrite(R1, LOW);
    delay(250);
  }
