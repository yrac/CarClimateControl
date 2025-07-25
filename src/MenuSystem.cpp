#include "MenuSystem.h"

bool menuActive = false;
int menuValue = 0;

void MenuSystem::begin() {
  // Initialize menu state
  menuActive = false;
  menuValue = 0;
}

void MenuSystem::update(SensorManager& sensors) {
  // Dummy example: no real menu interaction yet
  menuActive = false;
  menuValue = sensors.getSetpoint();
}

bool MenuSystem::isInMenu() {
  return menuActive;
}

int MenuSystem::getCurrentValue() {
  return menuValue;
}
