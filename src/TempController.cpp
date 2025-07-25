#include "TempController.h"
#include "EEPROMManager.h"
#include "DisplayManager.h"
#include "PinConfig.h"

extern EEPROMManager config;
extern DisplayManager display;

#define TEMP_MIN 5.0
#define TEMP_MAX 18.0
#define HYSTERESIS 1.0

void TempController::begin() {}

void TempController::update(float actualTemp) {
  uint16_t potLow = config.getConfig().potLow;
  uint16_t potHigh = config.getConfig().potHigh;

  int raw = analogRead(PIN_TEMP_POT);
  raw = constrain(raw, potLow, potHigh);

  float percent = (float)(raw - potLow) / (float)(potHigh - potLow);
  targetTemp = TEMP_MIN + percent * (TEMP_MAX - TEMP_MIN);

  // Hysteresis logic
  if (actualTemp > targetTemp + HYSTERESIS) {
    compressorAllowed = true;
  } else if (actualTemp < targetTemp - HYSTERESIS) {
    compressorAllowed = false;
  }
}

float TempController::getTargetTemp() {
  return targetTemp;
}

bool TempController::shouldCompressorRun() {
  return compressorAllowed;
}