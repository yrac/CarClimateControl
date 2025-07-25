#include "EEPROMManager.h"
#include <EEPROM.h>

const int ADDR_SETPOINT = 0;

void EEPROMManager::begin() {
  // Tidak perlu EEPROM.begin() pada Arduino Uno/Mega
}

void EEPROMManager::saveSetpoint(int value) {
  EEPROM.write(ADDR_SETPOINT, value);
}

int EEPROMManager::loadSetpoint() {
  int val = EEPROM.read(ADDR_SETPOINT);
  if (val < 5 || val > 18) {
    val = 10; // default
  }
  return val;
}
