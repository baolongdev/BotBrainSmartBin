#ifndef BotBrainSmartBin_H
#define BotBrainSmartBin_H

#include <Arduino.h>
#include <Servo.h>

class BotBrainSmartBin {
private:
  Servo myservo;         // Servo object to control the bin lid
  int servoPin;          // Servo pin
  int pingPin;           // Trigger Pin of Ultrasonic Sensor
  int echoPin;           // Echo Pin of Ultrasonic Sensor
  int openPosition;      // Position of the servo when the bin is open
  int closePosition;     // Position of the servo when the bin is closed

  unsigned long previousMicros; // Previous time for interval tracking
  int interval; 

  void moveServoTo(int position);
  float ultrasonicMeasure();

public:
  BotBrainSmartBin(int servoPin, int triggerPin, int echoPin, int openPos = 100, int closePos = 0, int interval = 15000);
  // Setup function to initialize smart bin
  void setupAllSmartBin(int servoPin, int triggerPin, int echoPin);

  // Functions to open and close the bin
  void MoThungRac();
  void DongThungRac();

  // Function to get distance from ultrasonic sensor
  float getDistance();

  bool timeToUpdate();
};

#endif  // BotBrainSmartBin_H
