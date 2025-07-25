#include "DisplayManager.h"
#include "SensorManager.h"
#include "MenuSystem.h"
#include "CompressorLogic.h"
#include <TM1637Display.h>
#include "PinConfig.h"

TM1637Display tmDisplay(PIN_TM1637_CLK, PIN_TM1637_DIO);

void DisplayManager::begin() {
  tmDisplay.setBrightness(0x0f);
}

void DisplayManager::showInit() {
  tmDisplay.showNumberDec(0, false);
  delay(200);
  tmDisplay.showNumberDec(88, true);
  delay(200);
  tmDisplay.clear();
}

void DisplayManager::update(SensorManager& sensors, MenuSystem& menu, CompressorLogic& logic) {
  // Simplified example logic
  if (menu.isInMenu()) {
    tmDisplay.showNumberDec(menu.getCurrentValue(), true);
  } else if (logic.isFreezeCleaning()) {
    tmDisplay.showNumberDec(1234); // example code for "CL"
  } else {
    tmDisplay.showNumberDec(sensors.getCurrentTemperature(), true);
  }
}