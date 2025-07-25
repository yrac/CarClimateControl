#include "InputManager.h"
#include "PinConfig.h"

#define DEBOUNCE_MS 30
#define LONG_PRESS_MS 1000

void InputManager::begin() {
  pinMode(PIN_BTN_FREEZE, INPUT_PULLUP);
}

void InputManager::update() {
  bool state = digitalRead(PIN_BTN_FREEZE) == LOW;

  if (state != lastState) {
    delay(DEBOUNCE_MS);
    lastState = state;
  }

  if (state && pressStart == 0) {
    pressStart = millis();
  }

  if (!state && pressStart > 0) {
    unsigned long duration = millis() - pressStart;
    if (duration >= LONG_PRESS_MS) {
      longPressDetected = true;
    } else {
      shortPressDetected = true;
    }
    pressStart = 0;
  }
}

bool InputManager::isShortPress() {
  if (shortPressDetected) {
    shortPressDetected = false;
    return true;
  }
  return false;
}

bool InputManager::isLongPress() {
  if (longPressDetected) {
    longPressDetected = false;
    return true;
  }
  return false;
}

bool InputManager::isPressed() {
  return digitalRead(PIN_BTN_FREEZE) == LOW;
}