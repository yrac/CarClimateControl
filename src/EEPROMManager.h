#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>

struct ACConfig {
  bool bypassMode;
  uint16_t operationHours;
  uint16_t potMin;
  uint16_t potMax;
  int opHour; 
};

class EEPROMManager {
public:
  void begin();
  void save();
  void reset();

  ACConfig& getConfig();
};

#endif
