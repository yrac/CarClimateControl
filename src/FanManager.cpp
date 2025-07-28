#include "FanManager.h"
#include <Arduino.h>

FanManager::FanManager(int outputPin) {
    _pin = outputPin;
    _state = FAN_OFF;
}

void FanManager::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void FanManager::turnOn() {
    digitalWrite(_pin, HIGH);
    _state = FAN_ON;
}

void FanManager::turnOff() {
    digitalWrite(_pin, LOW);
    _state = FAN_OFF;
}

void FanManager::loop(bool compressorActive, bool fastCooling) {
    if (compressorActive || fastCooling) {
        turnOn();
    } else {
        turnOff();
    }
}

FanState FanManager::getState() {
    return _state;
}