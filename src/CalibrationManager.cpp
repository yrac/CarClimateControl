#include "CalibrationManager.h"
#include "EEPROMManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "BuzzerManager.h"

extern EEPROMManager config;
extern DisplayManager display;
extern InputManager input;
extern BuzzerManager buzzer;

void CalibrationManager::begin() {
  state = CAL_WAIT_LO;
  display.showWord("LO  ");
}

void CalibrationManager::update() {
  if (state == CAL_IDLE || millis() - lastDisplayUpdate < 500) return;

  lastDisplayUpdate = millis();

  switch (state) {
    case CAL_WAIT_LO:
      if (input.isPressed()) {
        config.getConfig().potLow = analogRead(PIN_TEMP_POT);
        display.showWord("HI  ");
        state = CAL_WAIT_HI;
        buzzer.beep(BEEP_SHORT);
      }
      break;

    case CAL_WAIT_HI:
      if (input.isPressed()) {
        config.getConfig().potHigh = analogRead(PIN_TEMP_POT);
        config.save();
        display.showWord("OK  ");
        buzzer.beep(BEEP_LONG);
        state = CAL_DONE;
      }
      break;

    case CAL_DONE:
      // Wait 2s then exit
      if (millis() - lastDisplayUpdate > 2000) {
        state = CAL_IDLE;
      }
      break;

    default:
      break;
  }
}

bool CalibrationManager::isCalibrating() {
  return state != CAL_IDLE;
}