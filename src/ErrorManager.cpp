#include "ErrorManager.h"
#include "SensorManager.h"
#include "EEPROMManager.h"
#include "DisplayManager.h"
#include "BuzzerManager.h"

extern SensorManager sensors;
extern EEPROMManager config;
extern DisplayManager display;
extern BuzzerManager buzzer;

static ErrorCode currentError = ERR_NONE;

void ErrorManager::begin() {}

void ErrorManager::update() {
  float temp = sensors.getEvapTemperature();

  if (isnan(temp) || temp < -40 || temp > 100) {
    currentError = ERR_SENSOR_RANGE;
  } else if (config.getConfig().magic != EEPROM_MAGIC) {
    currentError = ERR_EEPROM_CORRUPT;
  } else {
    currentError = ERR_NONE;
  }

  if (currentError != ERR_NONE) {
    buzzer.beepPersistent();
    display.showWord(getErrorText());
  }
}

ErrorCode ErrorManager::getError() {
  return currentError;
}

const char* ErrorManager::getErrorText() {
  switch (currentError) {
    case ERR_SENSOR_DISCONNECTED: return "SNS ";
    case ERR_SENSOR_RANGE:        return "RANG";
    case ERR_EEPROM_CORRUPT:      return "EEP ";
    default:                      return "    ";
  }
}

bool ErrorManager::hasError() {
  return currentError != ERR_NONE;
}