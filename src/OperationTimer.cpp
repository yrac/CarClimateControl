#include "OperationTimer.h"
#include "EEPROMManager.h"

extern EEPROMManager config;

static unsigned long lastUpdate = 0;
static unsigned long activeTime = 0;

void OperationTimer::begin() {
  lastUpdate = millis();
}

void OperationTimer::update(bool compressorOn) {
  if (!compressorOn) {
    lastUpdate = millis();  // update titik waktu terakhir
    return;
  }

  unsigned long now = millis();
  unsigned long elapsed = now - lastUpdate;

  // Akumulasi hanya jika lebih dari 60.000 ms (1 menit)
  if (elapsed >= 60000) {
    lastUpdate = now;
    config.getConfig().operationHours++;
    config.save();
  }
}

uint16_t OperationTimer::getHours() {
  return config.getConfig().operationHours;
}

void OperationTimer::reset() {
  config.getConfig().operationHours = 0;
  config.save();
}