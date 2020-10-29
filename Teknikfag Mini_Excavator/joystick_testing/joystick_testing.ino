// Module KY023
int LXpin= A15; // Left x Input Pin
int LYpin = A14; // Left y Input Pin
int RXpin= A13; // Right x Input Pin
int RYpin = A12; // Right y Input Pin

int lx, ly, rx, ry = 0; // Left and right x and y placeholder values
int LXval, LYval, RXval, RYval = 0; // Left and right x and y values

int upperThreshold = 600; // Upper threshold for joysticks
int lowerThreshold = 500; // Lower threshold for joysticks

void setup () {
 Serial.begin (9600);
}
void loop () {

 lx = analogRead (LXpin);
 ly = analogRead (LYpin);
 rx = analogRead (RXpin);
 ry = analogRead (RYpin);

 if(lx >= upperThreshold){
  LXval = 1;
 } else if (lx <= lowerThreshold) {
    LXval = -1;
   } else {
      LXval = 0;
     }

 if(rx >= upperThreshold){
  RXval = 1;
 } else if (rx <= lowerThreshold) {
    RXval = -1;
   } else {
      RXval = 0;
     }

 if(ly >= upperThreshold){
  LYval = 1;
 } else if (ly <= lowerThreshold) {
    LYval = -1;
   } else {
      LYval = 0;
     }

 if(ry >= upperThreshold){
  RYval = 1;
 } else if (ry <= lowerThreshold) {
    RYval = -1;
   } else {
      RYval = 0;
     }

 Serial.print("LX = ");
 Serial.println (LXval, DEC);
 Serial.print("LY = ");
 Serial.println (LYval, DEC);/*
 Serial.print ("RX = ");
 Serial.println (RXval, DEC);
 Serial.print ("RY = ");
 Serial.println (RYval, DEC);*/
 Serial.println("");

 delay (100);
 
}
