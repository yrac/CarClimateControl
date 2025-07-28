#include "TempSensor.h"
#include <Arduino.h>

TempSensor::TempSensor(int pin) {
    _pin = pin;
}

float TempSensor::readADC() {
    return analogRead(_pin);
}

float TempSensor::readTemperature() {
    int adcValue = analogRead(_pin);
    float resistance = (1023.0 / adcValue - 1.0) * 10000.0;

    float steinhart;
    steinhart = resistance / 10000.0;                  // (R/Ro)
    steinhart = log(steinhart);                        // ln(R/Ro)
    steinhart = 1.0 / (25.0 + 273.15 + (steinhart / 3950.0)); // 1/T = 1/To + 1/B * ln(R/Ro)
    steinhart = steinhart - 273.15;                    // Convert to °C

    return steinhart;
}