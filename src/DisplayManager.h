#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
class SensorManager;
class MenuSystem;
class CompressorLogic;

class DisplayManager {
public:
  void begin();
  void showInit();
  void update(SensorManager& sensors, MenuSystem& menu, CompressorLogic& logic);
};

#endif // DISPLAY_MANAGER_H
