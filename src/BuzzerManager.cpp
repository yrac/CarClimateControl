#include <Arduino.h>
#include "BuzzerManager.h"
#include "PinConfig.h"

static bool buzzerMuted = false;
static unsigned long beepStartTime = 0;
static unsigned int beepDuration = 0;
static bool beeping = false;

void BuzzerManager::begin() {
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

void BuzzerManager::beep(BeepType type) {
  if (buzzerMuted) return;

  switch (type) {
    case BEEP_SHORT:  beepDuration = 100; break;
    case BEEP_LONG:   beepDuration = 500; break;
    case BEEP_ERROR:  beepDuration = 3000; break;
  }

  digitalWrite(PIN_BUZZER, HIGH);
  beepStartTime = millis();
  beeping = true;
}

void BuzzerManager::update() {
  if (beeping && millis() - beepStartTime > beepDuration) {
    digitalWrite(PIN_BUZZER, LOW);
    beeping = false;
  }
}

void BuzzerManager::mute(bool m) {
  buzzerMuted = m;
}