#include "OperationHourManager.h"
#include <Arduino.h>

OperationHourManager::OperationHourManager() {
    _lastOnTime = 0;
    _totalMillis = 0;
    _wasOn = false;
}

void OperationHourManager::begin() {
    _totalMillis = 0;
    _lastOnTime = 0;
    _wasOn = false;
}

void OperationHourManager::loop(bool compressorOn) {
    unsigned long now = millis();

    if (compressorOn && !_wasOn) {
        _lastOnTime = now;
        _wasOn = true;
    } else if (!compressorOn && _wasOn) {
        _totalMillis += (now - _lastOnTime);
        _wasOn = false;
    }
}

unsigned long OperationHourManager::getHours() {
    return (_totalMillis + (_wasOn ? millis() - _lastOnTime : 0)) / 3600000UL;
}

unsigned long OperationHourManager::getMinutes() {
    return (_totalMillis + (_wasOn ? millis() - _lastOnTime : 0)) / 60000UL;
}