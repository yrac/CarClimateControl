#include "BuzzerManager.h"
#include "PinConfig.h"

#define SHORT_DURATION 100
#define LONG_DURATION  400
#define DOUBLE_GAP     150

void BuzzerManager::begin() {
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

void BuzzerManager::update() {
  if (currentBeep == BEEP_NONE) return;

  unsigned long now = millis();

  switch (currentBeep) {
    case BEEP_SHORT:
      if (now - beepStart < SHORT_DURATION) {
        digitalWrite(PIN_BUZZER, HIGH);
      } else {
        digitalWrite(PIN_BUZZER, LOW);
        currentBeep = BEEP_NONE;
      }
      break;

    case BEEP_LONG:
      if (now - beepStart < LONG_DURATION) {
        digitalWrite(PIN_BUZZER, HIGH);
      } else {
        digitalWrite(PIN_BUZZER, LOW);
        currentBeep = BEEP_NONE;
      }
      break;

    case BEEP_DOUBLE:
      if (now - beepStart < SHORT_DURATION) {
        digitalWrite(PIN_BUZZER, HIGH);
      } else if (now - beepStart < SHORT_DURATION + DOUBLE_GAP) {
        digitalWrite(PIN_BUZZER, LOW);
      } else if (now - beepStart < SHORT_DURATION * 2 + DOUBLE_GAP) {
        digitalWrite(PIN_BUZZER, HIGH);
      } else {
        digitalWrite(PIN_BUZZER, LOW);
        currentBeep = BEEP_NONE;
      }
      break;

    case BEEP_PERSISTENT:
      digitalWrite(PIN_BUZZER, HIGH);
      break;

    default:
      digitalWrite(PIN_BUZZER, LOW);
      break;
  }
}

void BuzzerManager::beep(BeepType type) {
  beepStart = millis();
  currentBeep = type;
}

void BuzzerManager::beepPersistent() {
  currentBeep = BEEP_PERSISTENT;
}

void BuzzerManager::stop() {
  digitalWrite(PIN_BUZZER, LOW);
  currentBeep = BEEP_NONE;
}