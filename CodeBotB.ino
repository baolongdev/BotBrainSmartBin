#include "BotBrainSmartBin.h"
#include <Arduino.h>

// Define pin numbers
const int SERVO_PIN = 9;
const int TRIGGER_PIN = 7;
const int ECHO_PIN = 6;
// const int openPosition;
// const int closePosition;
bool flash = true;  //MoThungRac();

// Create an instance of the BotBrainSmartBin class
BotBrainSmartBin smartBin(SERVO_PIN, TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  smartBin.setupAllSmartBin(SERVO_PIN, TRIGGER_PIN, ECHO_PIN);
  smartBin.DongThungRac();
}

void loop() {
  // Call getDistance to get the distance from the ultrasonic sensor
  float distance = smartBin.getDistance();
  if (smartBin.timeToUpdate()) {
    // Serial.println(distance);
    if (distance < 15 && flash) {
      smartBin.MoThungRac();  // Open the bin lid
      flash = false;          // Update the check flag
    } else if (distance > 90) {
      smartBin.DongThungRac();  // Close the bin lid
      flash = true;            // Update the check flag
    }
  }
}
