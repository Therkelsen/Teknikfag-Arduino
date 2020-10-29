  
  // Include the library needed for controlling a stepper motor
  #include <Stepper.h>
  
  // Amount of steps the stepper must turn for one full revolution
  const int stepsPerRev = 200;
  
  // Stepper pins // Stepper pins defined to pins 3 through 6
  #define AA 3
  #define AB 4
  #define BA 5
  #define BB 6
  
  // Initialize the stepper library with stepsPerRev amount of steps per revolution
  Stepper rotate(stepsPerRev, AA, AB, BA, BB);
  
  // Rotation value needed for sorting colors with the step motor
  int rotVal = 200;
  
  // Relay pin
  #define R1 2
  int relState = LOW;
  
  // Color sensor pins
  #define S0 8
  #define S1 9
  #define S2 10
  #define S3 11
  #define sensorOut 12
  
  // Stores color frequency read by the photodiodes
  int r, g, b = 0;
  
  // LED pins
  #define rPin 7
  #define gPin 6
  #define bPin 5
  
  // Variables needed for a timer
  unsigned long curMillis1, curMillis2, prevMillis1, prevMillis2 = 0;
  const long inter1 = 1000;
  const long inter2 = 1000;
  
  int m, h, d = 0;
  int loops = 0;
  
  // String for storing which color the color sensor registers
  String color;
  
  // Strings for storing status
  String motorStatus;
  String pistonStatus;
  
  void setup() {
    // Begins serial communication
    Serial.begin(9600);
    rotate.setSpeed(30);
  
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
  
    pinMode(rPin, INPUT);
    pinMode(gPin, INPUT);
    pinMode(bPin, INPUT);
  }
  
  void loop() {
    // Runs the custom functions made below
    rotate.step(200);
    //statusDisplay();
    //colorRead();
    //colorSort();
    //loops++;
  
    //    rotate.step(200);
    //    digitalWrite(7, HIGH);
    //    delay(500);
    //    digitalWrite(7, LOW);
    //    delay(500);
  
  }
  
  void colorRead() {
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    r = pulseIn(sensorOut, LOW);
    digitalWrite(rPin, 255);
  
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    g = pulseIn(sensorOut, LOW);
    digitalWrite(gPin, 255);
  
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    b = pulseIn(sensorOut, LOW);
    digitalWrite(bPin, 255);
    
    /*
    // Checks the color based on the frequencies
    if (50 < r && r < 150 && 125 < g && g < 280 && 125 < b && b < 220) {
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
      rotVal = -75;
    } else if (0 < r && r < 25 && 0 < g && b < 25 && 0 < g && g < 25) {
      color = "White";
      rotVal = -50;
    } else if (1 == 2) {
      color = "Default";
      rotVal = -25;
    }*/
  }
  
  void colorSort() {
    // Updates the timer
    curMillis2 = millis();
    // Rotate based on color found and extend the piston, then returns to original position
    if (curMillis2 - prevMillis2 >= inter2) {
      prevMillis2 = curMillis2;
      if (relState == LOW && color != NULL) {
        rotate.step(rotVal);
        relState = HIGH;
        motorStatus = "Rotating motor " + String(rotVal) + " steps forward";
        pistonStatus = "Extending piston";
      } else {
        relState = LOW;
        rotate.step(-rotVal);
        motorStatus = "Rotating motor " + String(rotVal) + " steps backwards";
        pistonStatus = "Retracting piston";
      }
      digitalWrite(R1, relState);
    }
  
    if (relState == LOW) {
      motorStatus = "Motor is stationary";
      pistonStatus = "Piston is stationary";
    }
  }
  
  void statusDisplay() {
    curMillis1 = millis();
  
    // Prints the color frequencies and registered color in the serial monitor every time a given interval has passed
    if (curMillis1 - prevMillis1 >= inter1) {
      prevMillis1 = curMillis1;
  
      Serial.println("--------------------");
      Serial.println("TIME:");
      Serial.print("Time passed since start: ");
      Serial.print(millis() / 1000);
      Serial.println(" seconds");
  
      Serial.print("Times looped since start: ");
      Serial.println(loops);
      Serial.println();
  
      Serial.println("COLOR:");
      Serial.print("Raw frequencies: ");
      Serial.print(r);
      Serial.print(",  ");
      Serial.print(g);
      Serial.print(",  ");
      Serial.println(b);
      Serial.print("Color: ");
      Serial.println(color);
      Serial.println();
  
      Serial.println("STATUS:");
      Serial.println(motorStatus);
      Serial.println(pistonStatus);
      Serial.println("--------------------");
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
    }
  }
