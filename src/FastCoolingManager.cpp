#include "FastCoolingManager.h"

#define FAST_COOLING_TRIGGER_TEMP 30.0

void FastCoolingManager::begin() {
  active = false;
}

void FastCoolingManager::update(float actualTemp, float targetTemp) {
  // Jika suhu sangat panas dan target jauh lebih dingin
  if (actualTemp > FAST_COOLING_TRIGGER_TEMP && actualTemp > targetTemp + 5) {
    active = true;
  } 
  // Matikan fast cooling jika suhu sudah cukup turun
  else if (actualTemp <= FAST_COOLING_TRIGGER_TEMP) {
    active = false;
  }
}

bool FastCoolingManager::shouldDelayCompressor() {
  return active;
}

bool FastCoolingManager::isActive() {
  return active;
}