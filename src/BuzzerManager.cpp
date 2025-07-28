#include "BuzzerManager.h"
#include <Arduino.h>

BuzzerManager::BuzzerManager(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    _beepUntil = 0;
}

void BuzzerManager::beep(int duration) {
    digitalWrite(_pin, HIGH);
    _beepUntil = millis() + duration;
}

void BuzzerManager::loop() {
    if (_beepUntil > 0 && millis() > _beepUntil) {
        digitalWrite(_pin, LOW);
        _beepUntil = 0;
    }
}