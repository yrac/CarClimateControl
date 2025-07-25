#include "EEPROMManager.h"
#include <EEPROM.h>

static ACConfig config;

void EEPROMManager::begin() {
  EEPROM.begin(sizeof(ACConfig));
  EEPROM.get(0, config);

  // Validasi sederhana
  if (config.potMin == 0xFFFF || config.potMax == 0xFFFF || config.potMax < config.potMin) {
    config.potMin = 0;
    config.potMax = 1023;
    config.bypassMode = false;
    config.operationHours = 0;
    save();
  }
}

void EEPROMManager::save() {
  EEPROM.put(0, config);
  EEPROM.commit();  // Untuk board berbasis ESP. Bisa diabaikan di board AVR.
}

void EEPROMManager::reset() {
  config.bypassMode = false;
  config.operationHours = 0;
  config.potMin = 0;
  config.potMax = 1023;
  save();
}

ACConfig& EEPROMManager::getConfig() {
  return config;
}
