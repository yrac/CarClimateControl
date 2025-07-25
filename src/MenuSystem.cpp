#include "MenuSystem.h"
#include "PinConfig.h"
#include "DisplayManager.h"
#include "SensorManager.h"
#include "EEPROMManager.h"
#include "OperationTimer.h"
#include "CompressorLogic.h"

extern DisplayManager display;
extern SensorManager sensor;
extern EEPROMManager config;
extern OperationTimer timer;
extern CompressorLogic compressor;

void MenuSystem::begin() {
  pinMode(PIN_FREEZE_BUTTON, INPUT_PULLUP);
  currentState = MODE_IDLE;
  inMenu = false;
  buttonLastState = HIGH;
  buttonPressTime = 0;
}

void MenuSystem::update() {
  handleButton();

  // Tindakan saat dalam menu
  if (inMenu) {
    switch (currentState) {
      case MODE_MENU_OPHR:
        display.showWord("OPHr");
        delay(1000);
        display.showOphr(timer.getHours());
        break;

      case MODE_MENU_BYPASS:
        display.showWord(compressor.isBypassEnabled() ? "BPOn" : "BPOF");
        delay(1500);
        compressor.toggleBypass();
        exitMenu();
        break;

      case MODE_MENU_RESET_EEPROM:
        display.showWord("rSt ");
        delay(1000);
        config.reset();
        display.showWord("done");
        delay(1000);
        exitMenu();
        break;

      case MODE_CALIBRATE:
        display.showWord("CAL ");
        delay(1500);
        sensor.calibratePot();
        display.showWord("done");
        delay(1000);
        exitMenu();
        break;

      default:
        break;
    }
  }
}

void MenuSystem::handleButton() {
  bool state = digitalRead(PIN_FREEZE_BUTTON);

  if (state == LOW && buttonLastState == HIGH) {
    buttonPressTime = millis();
  } else if (state == HIGH && buttonLastState == LOW) {
    unsigned long pressDuration = millis() - buttonPressTime;

    if (pressDuration >= 3000) {
      // Long press → masuk menu berikutnya
      inMenu = true;

      if (currentState == MODE_IDLE || currentState == MODE_FREEZE_CLEAN)
        currentState = MODE_MENU_OPHR;
      else if (currentState == MODE_MENU_OPHR)
        currentState = MODE_MENU_BYPASS;
      else if (currentState == MODE_MENU_BYPASS)
        currentState = MODE_MENU_RESET_EEPROM;
      else if (currentState == MODE_MENU_RESET_EEPROM)
        currentState = MODE_CALIBRATE;
      else
        exitMenu();

    } else {
      // Short press → jalankan freeze cleaning jika tidak sedang dalam menu
      if (!inMenu) {
        currentState = MODE_FREEZE_CLEAN;
      }
    }
  }

  buttonLastState = state;
}

void MenuSystem::exitMenu() {
  currentState = MODE_IDLE;
  inMenu = false;
}

MenuState MenuSystem::getState() {
  return currentState;
}

bool MenuSystem::isInMenu() {
  return inMenu || currentState != MODE_IDLE;
}
