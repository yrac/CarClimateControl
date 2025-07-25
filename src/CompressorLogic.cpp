#include "CompressorLogic.h"
#include "PinConfig.h"
#include <Arduino.h>

bool freezeActive = false;

void CompressorLogic::begin() {
  pinMode(PIN_COMPRESSOR_RELAY, OUTPUT);
  digitalWrite(PIN_COMPRESSOR_RELAY, LOW); // Kompresor awal OFF
}

void CompressorLogic::update(SensorManager& sensors, MenuSystem& menu, EEPROMManager& eeprom) {
  int currentTemp = sensors.getCurrentTemperature();
  int setpoint = sensors.getSetpoint();

  if (freezeActive) {
    if (currentTemp <= -5) {
      digitalWrite(PIN_COMPRESSOR_RELAY, LOW);
      freezeActive = false;
    } else {
      digitalWrite(PIN_COMPRESSOR_RELAY, HIGH);
    }
  } else {
    if (currentTemp > setpoint) {
      digitalWrite(PIN_COMPRESSOR_RELAY, HIGH);
    } else {
      digitalWrite(PIN_COMPRESSOR_RELAY, LOW);
    }
  }
}

bool CompressorLogic::isFreezeCleaning() {
  return freezeActive;
}
