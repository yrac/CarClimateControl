#ifndef COMPRESSOR_LOGIC_H
#define COMPRESSOR_LOGIC_H

#include "SensorManager.h"
#include "MenuSystem.h"
#include "EEPROMManager.h"

class CompressorLogic {
public:
  void begin();
  void update(SensorManager& sensors, MenuSystem& menu, EEPROMManager& eeprom);
  bool isFreezeCleaning();
};

#endif // COMPRESSOR_LOGIC_H
