#include "CompressorManager.h"
#include <Arduino.h>

CompressorManager::CompressorManager(int outputPin) {
    _pin = outputPin;
    _state = COMP_OFF;
    _lastSwitchTime = 0;
    _minOnTime = 10000;  // 10 detik minimum ON
    _minOffTime = 5000;  // 5 detik minimum OFF
}

void CompressorManager::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

CompressorState CompressorManager::getState() {
    return _state;
}

void CompressorManager::setECUAllowed(bool allowed) {
    _ecuAllowed = allowed;
}

void CompressorManager::setBypassECU(bool bypass) {
    _bypassECU = bypass;
}

bool CompressorManager::isBypassECU() const {
    return _bypassECU;
}

unsigned long CompressorManager::getOperationHours() const {
    return _operationHours / 3600000UL;
}

void CompressorManager::resetOperationHours() {
    _operationHours = 0;
}

void CompressorManager::setAdaptiveTarget(float adaptiveTarget) {
    _adaptiveTarget = adaptiveTarget;
}

void CompressorManager::setErrorState(int errorCode) {
    _errorState = errorCode;
}

int CompressorManager::getErrorState() const {
    return _errorState;
}

void CompressorManager::updateOperationHours() {
    if (_state == COMP_ON) {
        _operationHours += 10; // Asumsikan loop dipanggil setiap 10ms
    }
}

void CompressorManager::loop(float currentTemp, float targetTemp, bool freezeActive, bool fastCooling) {
    unsigned long now = millis();
    updateOperationHours();

    // Freeze cleaning → matikan kompresor
    if (freezeActive) {
        turnOff();
        return;
    }

    // Fast cooling → selalu ON
    if (fastCooling) {
        if (_state == COMP_OFF && (now - _lastSwitchTime >= _minOffTime)) {
            turnOn();
        }
        return;
    }

    // Adaptive cooling
    float effectiveTarget = (_adaptiveTarget > 0) ? _adaptiveTarget : targetTemp;
    float diff = currentTemp - effectiveTarget;

    // Proteksi error: suhu tidak turun/tidak wajar
    if (currentTemp < -10 || currentTemp > 70) {
        setErrorState(1); // Error suhu ekstrem
        turnOff();
        return;
    } else {
        setErrorState(0);
    }

    // Izin ECU dan bypass
    bool allowed = _ecuAllowed || _bypassECU;

    if (!allowed) {
        turnOff();
        return;
    }

    if (_state == COMP_ON) {
        if (diff < -0.5 && (now - _lastSwitchTime >= _minOnTime)) {
            turnOff();
        }
    } else if (_state == COMP_OFF) {
        if (diff > 0.5 && (now - _lastSwitchTime >= _minOffTime)) {
            turnOn();
        }
    }
}

void CompressorManager::turnOn() {
    digitalWrite(_pin, HIGH);
    _state = COMP_ON;
    _lastSwitchTime = millis();
}

void CompressorManager::turnOff() {
    digitalWrite(_pin, LOW);
    _state = COMP_OFF;
    _lastSwitchTime = millis();
}