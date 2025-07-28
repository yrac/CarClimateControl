#include "Potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin) {
    _pin = pin;
    _rawLo = 0;
    _rawHi = 1023;
}

void Potentiometer::calibrate(int lo, int hi) {
    _rawLo = lo;
    _rawHi = hi;
}

void Potentiometer::setCalibrationPoints(int rawLo, int rawHi) {
    _rawLo = rawLo;
    _rawHi = rawHi;
}

int Potentiometer::getRawValue() {
    return analogRead(_pin);
}

float Potentiometer::getNormalized() {
    int val = getRawValue();
    val = constrain(val, _rawLo, _rawHi);
    return float(val - _rawLo) / (_rawHi - _rawLo);
}

float Potentiometer::getTargetTemperature(float minTemp, float maxTemp) {
    return minTemp + getNormalized() * (maxTemp - minTemp);
}