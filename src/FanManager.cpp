#include "FanManager.h"
#include "PinConfig.h"

void FanManager::begin() {
  pinMode(PIN_FAN_RELAY_LOW, OUTPUT);
  pinMode(PIN_FAN_RELAY_MED, OUTPUT);
  pinMode(PIN_FAN_RELAY_HIGH, OUTPUT);
  pinMode(PIN_FAN_BYPASS, OUTPUT);

  digitalWrite(PIN_FAN_RELAY_LOW, HIGH);
  digitalWrite(PIN_FAN_RELAY_MED, HIGH);
  digitalWrite(PIN_FAN_RELAY_HIGH, HIGH);
  digitalWrite(PIN_FAN_BYPASS, LOW);
}

void FanManager::setMode(FanMode mode) {
  currentMode = mode;

  // Reset semua relays
  digitalWrite(PIN_FAN_RELAY_LOW, HIGH);
  digitalWrite(PIN_FAN_RELAY_MED, HIGH);
  digitalWrite(PIN_FAN_RELAY_HIGH, HIGH);
  digitalWrite(PIN_FAN_BYPASS, LOW);

  switch (mode) {
    case FAN_LOW:
      digitalWrite(PIN_FAN_RELAY_LOW, LOW);
      break;
    case FAN_MED:
      digitalWrite(PIN_FAN_RELAY_MED, LOW);
      break;
    case FAN_HIGH:
      digitalWrite(PIN_FAN_RELAY_HIGH, LOW);
      break;
    case FAN_FULL:
      digitalWrite(PIN_FAN_BYPASS, HIGH);
      break;
    case FAN_OFF:
    default:
      // Semua OFF
      break;
  }
}

void FanManager::update() {
  // Tidak perlu timer atau sensor, hanya setMode()
}

FanMode FanManager::getMode() {
  return currentMode;
}