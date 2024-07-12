#include "BotBrainSmartBin.h"
#include <Arduino.h>

// Define pin numbers
const int SERVO_PIN       =;
const int TRIGGER_PIN     =;
const int ECHO_PIN        =;
const int openPosition    =;
const int closePosition   =;
const int interval        =;
bool flash = true; // MoThungRac();

// Create an instance of the BotBrainSmartBin class
BotBrainSmartBin smartBin(SERVO_PIN, TRIGGER_PIN, ECHO_PIN, openPosition, closePosition, interval);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
}
