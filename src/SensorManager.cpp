#include "SensorManager.h"
#include <Arduino.h>
#include "PinConfig.h"

float currentTemp = 25.0;
int setpoint = 10;

void SensorManager::begin() {
  pinMode(PIN_NTC_SENSOR, INPUT);
  pinMode(PIN_POTENTIOMETER, INPUT);
}

void SensorManager::update() {
  int ntcRaw = analogRead(PIN_NTC_SENSOR);
  currentTemp = 3950.0 / (log(10000.0 * (1024.0 / ntcRaw - 1.0)) - 3950.0 / 298.15) - 273.15;

  int potRaw = analogRead(PIN_POTENTIOMETER);
  setpoint = map(potRaw, 0, 1023, 5, 18);
}

float SensorManager::getCurrentTemperature() {
  return currentTemp;
}

int SensorManager::getSetpoint() {
  return setpoint;
}
