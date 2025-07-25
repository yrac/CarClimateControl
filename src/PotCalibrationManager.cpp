#include "PotCalibrationManager.h"
#include "EEPROMManager.h"
#include "PinConfig.h"

extern EEPROMManager config;

void PotCalibrationManager::begin() {
  pinMode(PIN_POT, INPUT);
}

int PotCalibrationManager::readRaw() {
  return analogRead(PIN_POT);
}

float PotCalibrationManager::readMapped() {
  int raw = readRaw();
  uint16_t min = config.getConfig().potMin;
  uint16_t max = config.getConfig().potMax;

  // Hindari pembagian nol
  if (max <= min) max = min + 1;

  // Map ke suhu (5°C – 18°C)
  float ratio = (float)(raw - min) / (float)(max - min);
  ratio = constrain(ratio, 0.0f, 1.0f);

  return 5.0f + ratio * (18.0f - 5.0f);
}

void PotCalibrationManager::calibrate() {
  uint16_t minVal = 1023;
  uint16_t maxVal = 0;

  unsigned long start = millis();
  while (millis() - start < 3000) {
    int val = analogRead(PIN_POT);
    if (val < minVal) minVal = val;
    if (val > maxVal) maxVal = val;
    delay(10);
  }

  config.getConfig().potMin = minVal;
  config.getConfig().potMax = maxVal;
  config.save();
}