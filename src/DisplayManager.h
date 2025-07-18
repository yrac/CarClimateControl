#pragma once
#include <Arduino.h>
#include <TM1637Display.h>
#include "PinConfig.h"

class DisplayManager {
public:
  DisplayManager();
  void begin();
  void showInit();
  void showWord(const char* word);
  void showTempWithC(int temp);

private:
  TM1637Display _display;
};