#pragma once
#include "DisplayManager.h"
#include "PinConfig.h"

class ACController {
public:
  ACController(DisplayManager &display);
  void begin();
  void update();

private:
  DisplayManager &_display;
  float readNTC();
  float readSetpoint();

  float hysteresis = 1.0;
  bool freezeMode = false;
  bool freezeDone = false;
  unsigned long potMovedTime = 0;
  int lastPotRaw = 0;
  bool showingSetpoint = false;
};