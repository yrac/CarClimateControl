#include "OperationHourManager.h"
#include "EEPROMManager.h"
#include "DisplayManager.h"

extern EEPROMManager config;
extern DisplayManager display;

#define SERVICE_THRESHOLD_HOUR 500  // Misal servis tiap 500 jam
#define LOG_INTERVAL_MS        60000 // 1 menit

static unsigned long lastLog = 0;

void OperationHourManager::begin() {}

void OperationHourManager::update(bool compressorActive) {
  if (!compressorActive) return;

  if (millis() - lastLog >= LOG_INTERVAL_MS) {
    lastLog = millis();
    if (config.getConfig().opHour < 65535) {
      config.getConfig().opHour++;
      config.save();
    }
  }
}

uint16_t OperationHourManager::getHour() {
  return config.getConfig().opHour;
}

void OperationHourManager::reset() {
  config.getConfig().opHour = 0;
  config.save();
}

bool OperationHourManager::needsService() {
  return config.getConfig().opHour >= SERVICE_THRESHOLD_HOUR;
}