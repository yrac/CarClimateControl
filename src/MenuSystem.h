#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "SensorManager.h"

class MenuSystem {
public:
  void begin();
  void update(SensorManager& sensors);
  bool isInMenu();
  int getCurrentValue();
};

#endif // MENU_SYSTEM_H
