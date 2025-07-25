#include "BuzzerManager.h"
#include "PinConfig.h"
#include <Arduino.h>

void BuzzerManager::begin() {
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

void BuzzerManager::update(CompressorLogic& logic) {
  if (logic.isFreezeCleaning()) {
    tone(PIN_BUZZER, 2000, 100);  // beep pendek
  } else {
    noTone(PIN_BUZZER);
  }
}
