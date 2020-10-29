  
  // include the library code:
  #include <LiquidCrystal.h>
  
  // initialize the library by associating any needed LCD interface pin
  // with the arduino pin number it is connected to
  const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
  LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
  void setup() {
    lcd.begin(20, 4);
    lcd.print("Startup succesful");
  }
  
  void loop() {
  
  }
