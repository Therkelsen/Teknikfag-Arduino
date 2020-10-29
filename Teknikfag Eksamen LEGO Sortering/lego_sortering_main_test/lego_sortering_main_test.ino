
  /*
    Group 4 - Jonas Sundgaard, Jacob Feldbak & Thomas Therkelsen
    Mercantec - Viborg College of Technology

    Main software for mini excavator
    Sketch initiated 13/03-2019
    Latest update 14/06-2019
  */

  //      #######    ########     #######  #             #####     ########       ###      #########   ##########     #####     ##      #    #######
  //      #      #   #           #         #            #     #    #       #     #   #         #           #         #     #    # #     #   #       #
  //      #       #  #          #          #           #       #   #       #    #     #        #           #        #       #   #  #    #   #
  //      #       #  #####      #          #           #########   ########    #########       #           #        #       #   #   #   #    #######
  //      #       #  #          #          #           #       #   #       #   #       #       #           #        #       #   #    #  #           #
  //      #      #   #           #         #           #       #   #       #   #       #       #           #         #     #    #     # #   #       #
  //      #######    ########     #######  #########   #       #   #       #   #       #       #       #########      #####     #      ##    #######

  // Include the library needed for controlling a stepper motor
  #include <Stepper.h>

  // Steps per revolution (360 divided by angle degree increment pr. step)
  const int stepsPerRev = 200;
  // Stepper speed in RPM
  int stepSpd = 30;
  // Rotation value needed for sorting colors with the step motor
  int rotVal = 0;

  // Stepper pins
  #define AA 11
  #define AB 10
  #define BA 9
  #define BB 8

  // Initialize the stepper library with stepsPerRev amount of steps per revolution
  Stepper rotate(stepsPerRev, AA, AB, BA, BB);

  // Relay pin
  #define R1 12

  // Color sensor pins
  #define S0 6
  #define S1 7
  #define S2 4
  #define S3 5
  #define sensorOut 3

  // Stores color frequency read by the photodiodes
  int r, g, b = 0;
  int buff = 5;

  // Stores amount of bricks sorted
  int bricksSorted = 0;

  // Variables needed for timers
  unsigned long curMillis = 0;
  unsigned long prevMillis = 0;
  const long inter = 100;
  unsigned long loops = 0;

  // String for storing which color the color sensor registers
  String color = "None";

  //       #######    #########   #########   #        #   ########
  //      #       #   #               #       #        #   #       #
  //      #           #               #       #        #   #       #
  //       #######    #####           #       #        #   ########
  //              #   #               #       #        #   #
  //      #       #   #               #        #      #    #
  //       #######    #########       #         ######     #

  void setup() {
    // Begins serial communication
    Serial.begin(9600);
    Serial.println("--------------------");
    Serial.println("STARTING SETUP");
    Serial.println("Initializing sorting software");
    Serial.println("Setting stepper motor speed to " + String(stepSpd) + " RPM");
	// Sets motor speed
    rotate.setSpeed(stepSpd);

    // Setting the sensor pins and relay pins as output pins
    Serial.print("Setting color sensor pins (Pin ");
    Serial.println(String(S0) + ", " + String(S1) + ", "  + String(S2) + " & "  + String(S3) + ") to OUTPUT mode");
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    Serial.println("Setting relay pin (Pin " + String(R1) + ") to OUTPUT mode");
    pinMode(R1, OUTPUT);

    // Setting the sensorOut as input pin
    Serial.println("Setting color sensor out pin (Pin " + String(sensorOut) + ") to INPUT mode");
    pinMode(sensorOut, INPUT);

    // Setting frequency scaling to 20%
    Serial.println("Setting color sensor frequency scaling to 20%");
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
  }

  //      #              #####       #####     ########
  //      #             #     #     #     #    #       #
  //      #            #       #   #       #   #       #
  //      #            #       #   #       #   #######
  //      #            #       #   #       #   #
  //      #             #     #     #     #    #
  //      #########      #####       #####     #

  void loop() {
    // Runs the functions
    //statusDisplay();
    //colorRead();
    //delay(500);
    colorSort();
    //loops++;
  }

  //      ########    #########     #####     #######
  //      #       #   #            #     #    #      #
  //      #       #   #           #       #   #       #
  //      ########    #####       #########   #       #
  //      #       #   #           #       #   #       #
  //      #       #   #           #       #   #      #
  //      #       #   #########   #       #   #######

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
    if (95 - buff < r && r < 115 + buff && 190 - buff < g && g < 205 + buff && 145 - buff < b && b < 155 + buff) {
      color = "Red";
      rotVal = 25;
    } else if (130 - buff < r && r < 140 + buff && 95 - buff < g && g < 100 + buff && 90 - buff < b && b < 95 + buff) {
      color = "Green";
      rotVal = 50;
    } else if (150 - buff < r && r < 170 + buff && 90 - buff < g && g < 104 + buff && 55 - buff < b && b < 60 + buff) {
      color = "Blue";
      rotVal = 75;
    } else if (r == 0 && g == 0 && b == 0) {
      color = "None";
      rotVal = 0;
    } else {
      color = "Default";
      rotVal = -25;
    }
  }

  //       #######      #######     #########    ##########
  //      #       #    #       #    #        #        #
  //      #           #         #   #        #        #
  //       #######    #         #   #########         #
  //              #   #         #   #        #        #
  //      #       #    #       #    #        #        #
  //       #######      #######     #        #        #

  void colorSort() {
    /*if (rotVal != 0) {
      delay(1000);
      rotate.step(rotVal);
      delay(500);
      digitalWrite(R1, LOW);
      delay(100);
      digitalWrite(R1, HIGH);
      delay(1000);
      rotate.step(-rotVal);
    }*/
    delay(2500);
    rotate.step(25);
    delay(500);
    digitalWrite(R1, LOW);
    delay(100);
    digitalWrite(R1, HIGH);
    delay(1000);
    rotate.step(-25);

    delay(2500);
    rotate.step(75);
    delay(500);
    digitalWrite(R1, LOW);
    delay(100);
    digitalWrite(R1, HIGH);
    delay(1000);
    rotate.step(-75);

    delay(2500);
    rotate.step(50);
    delay(500);
    digitalWrite(R1, LOW);
    delay(100);
    digitalWrite(R1, HIGH);
    delay(1000);
    rotate.step(-50);
  }

  //       #######    #########     #####     #########   #       #    #######
  //      #       #       #        #     #        #       #       #   #       #
  //      #               #       #       #       #       #       #   #
  //       #######        #       #########       #       #       #    #######
  //              #       #       #       #       #       #       #           #
  //      #       #       #       #       #       #        #     #    #       #
  //       #######        #       #       #       #         #####      #######

  void statusDisplay() {
    curMillis = millis();

    // Prints the color frequencies and registered color in the serial monitor every time a given interval has passed
    if (true) {
      //curMillis - prevMillis >= inter
      prevMillis = curMillis;
      int sinceStart = millis() / 1000;

      Serial.println("--------------------");
      Serial.println("TIME:");
      Serial.println("Time passed since start: " + String(sinceStart) + " seconds");

      Serial.println("Times looped since start: " + String(loops));
      Serial.println();

      Serial.println("COLOR:");
      Serial.println("Raw frequencies: " + String(r) + ",  " + String(g) + ",  " + String(b));
      Serial.println("Color: " + String(color));
      Serial.println();

      Serial.println("Bricks sorted: " + String(bricksSorted));
      Serial.println("--------------------");
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
    }
  }
