#include "BotBrainSmartBin.h"
#include <Arduino.h>

BotBrainSmartBin::BotBrainSmartBin(int servoPin, int triggerPin, int echoPin, int openPos, int closePos, int interval)
  : servoPin(servoPin), pingPin(triggerPin), echoPin(echoPin), openPosition(openPos), closePosition(closePos), interval(interval), previousMicros(0) {
}

void BotBrainSmartBin::setupAllSmartBin(int servoPin, int triggerPin, int echoPin) {
  this->servoPin = servoPin;
  this->pingPin = triggerPin;
  this->echoPin = echoPin;
  myservo.attach(servoPin);  // attaches the servo to the specified pin
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void BotBrainSmartBin::MoThungRac() {
  moveServoTo(openPosition);
}

void BotBrainSmartBin::DongThungRac() {
  moveServoTo(closePosition);
}

float BotBrainSmartBin::getDistance() {
  float filterArray[20];  // array to store data samples from sensor
  float distance;         // store the distance from sensor

  // 1. Taking multiple measurements and storing in an array
  for (int sample = 0; sample < 20; sample++) {
    filterArray[sample] = ultrasonicMeasure();
    delay(30);  // to avoid ultrasonic interference
  }

  // 2. Sorting the array in ascending order
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (filterArray[i] > filterArray[j]) {
        float swap = filterArray[i];
        filterArray[i] = filterArray[j];
        filterArray[j] = swap;
      }
    }
  }

  // 3. Filtering noise and calculating the distance
  double sum = 0;
  for (int sample = 5; sample < 15; sample++) {
    sum += filterArray[sample];
  }

  distance = sum / 10;

  return distance;
}

float BotBrainSmartBin::ultrasonicMeasure() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  float distance_cm = 0.017 * duration_us;

  return distance_cm;
}

void BotBrainSmartBin::moveServoTo(int position) {
  myservo.write(position);
}

bool BotBrainSmartBin::timeToUpdate() {
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros;
    return true;
  }
  return false;
}
