#include "MQ135.h"

#define ANALOGPIN 0
float airthreshold[3] = {
  400, 400, 800};
  
  // Initialize the gas Sensor
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  // start the LEDs
  
  //Set up the serial terminal
  Serial.begin(9600); 
}
void loop() {
    float ppm = gasSensor.getPPM();
     
  Serial.println(ppm);
  Serial.print("a");


  delay(1000);
}
