#include "MenuManager.h"
#include "DisplayManager.h"
#include "BuzzerManager.h"
#include "CalibrationManager.h"
#include "OperationHourManager.h"
#include "EEPROMManager.h"

extern DisplayManager display;
extern BuzzerManager buzzer;
extern CalibrationManager calibration;
extern OperationHourManager opHour;
extern EEPROMManager config;

static MenuState currentMenu = MENU_NONE;
static unsigned long menuStartTime = 0;

#define MENU_TIMEOUT_MS 10000

void MenuManager::begin() {}

void MenuManager::handleButton(bool shortPress, bool longPress) {
  if (longPress && currentMenu == MENU_NONE) {
    currentMenu = MENU_CALIBRATE;
    menuStartTime = millis();
    buzzer.beep(BEEP_LONG);
  } else if (shortPress && currentMenu != MENU_NONE) {
    // Navigasi menu
    buzzer.beep(BEEP_SHORT);
    currentMenu = static_cast<MenuState>((currentMenu + 1) % (MENU_EXIT + 1));
    menuStartTime = millis();
  }
}

void MenuManager::update() {
  if (currentMenu == MENU_NONE) return;

  if (millis() - menuStartTime > MENU_TIMEOUT_MS) {
    currentMenu = MENU_NONE;
    buzzer.beep(BEEP_DOUBLE);
    return;
  }

  switch (currentMenu) {
    case MENU_CALIBRATE:
      display.showWord("CAL ");
      calibration.begin();
      break;

    case MENU_VIEW_OPH: {
      int hour = opHour.getHour();
      display.showNumber(hour);
      break;
    }

    case MENU_RESET_OPH:
      display.showWord("RST ");
      opHour.reset();
      buzzer.beep(BEEP_DOUBLE);
      break;

    case MENU_BYPASS_TOGGLE:
      config.getConfig().bypassMode = !config.getConfig().bypassMode;
      config.save();
      display.showWord(config.getConfig().bypassMode ? "BPON" : "BPOF");
      buzzer.beep(BEEP_SHORT);
      break;

    case MENU_EXIT:
      display.showWord("EXIT");
      currentMenu = MENU_NONE;
      buzzer.beep(BEEP_DOUBLE);
      break;

    default:
      break;
  }
}

bool MenuManager::inMenu() {
  return currentMenu != MENU_NONE;
}

void MenuManager::enter() {
    menuMode = true; 
}