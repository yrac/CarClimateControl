#include "FreezerManager.h"
#include "FanManager.h"
#include "CompressorManager.h"
#include "DisplayManager.h"
#include "BuzzerManager.h"

extern FanManager fan;
extern CompressorManager compressor;
extern DisplayManager display;
extern BuzzerManager buzzer;

#define FREEZE_TARGET_TEMP -5.0
#define FREEZE_DELAY_BLOWER_MS 1000

void FreezerManager::begin() {}

void FreezerManager::start() {
  if (state == FREEZE_IDLE) {
    fan.setMode(FAN_OFF);
    display.showWord("CL  ");
    state = FREEZE_COMPRESSOR_ON;
    stateStartTime = millis();
    buzzer.beep(BEEP_LONG);
  }
}

void FreezerManager::update(float currentTemp) {
  switch (state) {
    case FREEZE_IDLE:
      return;

    case FREEZE_COMPRESSOR_ON:
      compressor.update(true);
      if (currentTemp <= FREEZE_TARGET_TEMP) {
        compressor.forceStop();
        state = FREEZE_REACHED_TARGET;
        stateStartTime = millis();
      }
      break;

    case FREEZE_REACHED_TARGET:
      if (millis() - stateStartTime > FREEZE_DELAY_BLOWER_MS) {
        fan.setMode(FAN_FULL);
        state = FREEZE_BLOWER_ON;
        stateStartTime = millis();
      }
      break;

    case FREEZE_BLOWER_ON:
      if (millis() - stateStartTime > 3000) {
        state = FREEZE_IDLE;
        fan.setMode(FAN_OFF);
      }
      break;
  }
}

bool FreezerManager::isRunning() {
  return state != FREEZE_IDLE;
}