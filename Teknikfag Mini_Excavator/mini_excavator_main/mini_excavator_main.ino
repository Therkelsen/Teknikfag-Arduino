  
  /*
      Group 5 - Carl Emil, Caroline Ø & Thomas T
      Mercantec - Viborg College of Technology
  
      Main software for mini excavator
      Sketch initiated 08/12-2018
      Latest update 04/02-2019
  */
  
  // - START OF CODE - //
  
  //------------------- Include the LiquidCrystal library --------------------//
  #include <LiquidCrystal.h>
  
  //------------------- Create integers for holding LCD pins --------------------//
  int RS = 10;
  int EN = 9;
  int D4 = 8;
  int D5 = 7;
  int D6 = 6;
  int D7 = 5;
  
  //------------------- Create an LCD object using the LC lib --------------------//
  LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
  
  //------------------- Ints for joysticks --------------------//
  int LXpin = A5; // Left x Input Pin
  int LYpin = A6; // Left y Input Pin
  int RXpin = A3; // Right x Input Pin
  int RYpin = A4; // Right y Input Pin
  
  int LXtem, LYtem, RXtem, RYtem = 0; // Left and right x and y placeholder values
  int LXval, LYval, RXval, RYval = 0; // Left and right x and y values
  
  int upperThreshold = 900; // Upper threshold for joysticks
  int lowerThreshold = 100; // Lower threshold for joysticks
  
  boolean armOut, armUp = false; // Triggers for arm movement
  boolean armIn, armDown = true;
  
  int relIn1 = 3;
  int relIn2 = 2;
  
  unsigned long previousMillis = 0;        // will store last time LED was updated
  
  // constants won't change:
  const long interval = 500;           // interval at which to blink (milliseconds)
  
  //------------------- Everything that needs to be run once, goes here --------------------//
  void setup() {
    lcd.begin(20, 4); // Initiate the LCD screen
    pinMode(relIn1, OUTPUT);
    pinMode(relIn2, OUTPUT);
    lcd.setCursor(0, 0);
    lcd.print("Setup completed");
  }
  
  //------------------- Everything in here is run once every time the code cycles --------------------//
  void loop() {
    unsigned long currentMillis = millis();
    directionRead();
    armMovement();
    if (currentMillis - previousMillis >= interval) {
      directionPrint();
      previousMillis = currentMillis;
    }
  }
  
  void directionRead() {
    LXtem = analogRead (LXpin);
    LYtem = analogRead (LYpin);
    RXtem = analogRead (RXpin);
    RYtem = analogRead (RYpin);
  
    if (LXtem >= upperThreshold) {
      LXval = 1;
    } else if (LXtem <= lowerThreshold) {
      LXval = -1;
    } else {
      LXval = 0;
    }
  
    if (LYtem >= upperThreshold) {
      LYval = 1;
      armDown = true;
      armUp = false;
    } else if (LYtem <= lowerThreshold) {
      LYval = -1;
      armDown = false;
      armUp = true;
    } else {
      LYval = 0;
      armDown = false;
      armUp = false;
    }
  
    if (RXtem >= upperThreshold) {
      RXval = 1;
    } else if (RXtem <= lowerThreshold) {
      RXval = -1;
    } else {
      RXval = 0;
    }
  
    if (RYtem >= upperThreshold) {
      RYval = 1;
      armOut = true;
      armIn = false;
    } else if (RYtem <= lowerThreshold) {
      RYval = -1;
      armOut = false;
      armIn = true;
    } else {
      RYval = 0;
      armOut = false;
      armIn = false;
    }
  }
  
  void armMovement() {
    if (armUp == true) {
      digitalWrite(relIn1, HIGH);
    } else if (armDown == true) {
      digitalWrite(relIn1, LOW);
    }
  
    if (armOut == true) {
      digitalWrite(relIn2, HIGH);
    } else if (armIn == true) {
      digitalWrite(relIn2, LOW);
    }
  }
  
  void directionPrint() {
    lcd.clear();
  
    lcd.setCursor(0, 0);
    lcd.print("LX = ");
    lcd.setCursor(5, 0);
    lcd.print(LXval);
    lcd.setCursor(10, 0);
    lcd.print("LY = ");
    lcd.setCursor(15, 0);
    lcd.print(LYval);
  
    lcd.setCursor(0, 1);
    lcd.print("RX = ");
    lcd.setCursor(5, 1);
    lcd.print(RXval);
    lcd.setCursor(10, 1);
    lcd.print("RY = ");
    lcd.setCursor(15, 1);
    lcd.print(RYval);
  }
  
  // - END OF CODE - //
