
  // Color sensor pins
  #define S0 8
  #define S1 9
  #define S2 10
  #define S3 11
  #define sensorOut 12
  
  // Stores color frequency read by the photodiodes
  int r, g, b = 0;
  
  // String for storing which color the color sensor registers
  String color;
  
  void setup() {

    // Setting the outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(R1, OUTPUT);
  
    // Setting the sensorOut and relay pin as input pins
    pinMode(sensorOut, INPUT);
  
    // Setting frequency scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
  }
  
  void loop() {
    // Runs the custom function made below
    colorRead();
  }

  void colorRead() {
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    r = pulseIn(sensorOut, LOW);
  
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    g = pulseIn(sensorOut, LOW);
  
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    b = pulseIn(sensorOut, LOW);
  
    // Checks the color based on the frequencies
    if (110 < r && r < 150 && 180 < g && g < 280 && 125 < b && b < 220) {
      color = "Red";
      rotVal = 25;
    } else if (116 < r && r < 145 && 80 < g && g < 107 && 92 < b && b < 128) {
      color = "Green";
      rotVal = 50;
    } else if (180 < r && r < 255 && 98 < g && g < 130 && 50 < b && b < 76) {
      color = "Blue";
      rotVal = 75;
    } else if (48 < r && r < 90 && 60 < g && g < 100 && 89 < b && b < 135) {
      color = "Yellow";
      rotVal = 100;
    } else if (60 < r && r < 200 && 50 < g && b < 175 && 50 < g && g < 150) {
      color = "Black";
      rotVal = 75;
    } else if (0 < r && r < 25 && 0 < g && b < 25 && 0 < g && g < 25) {
      color = "White";
      rotVal = 50;
    }
  }