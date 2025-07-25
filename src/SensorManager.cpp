#include "SensorManager.h"
#include "PotCalibrationManager.h"
#include "PinConfig.h"

extern PotCalibrationManager pot;

static float currentTemp = 25.0;

#define NTC_BETA      3950.0
#define NTC_NOMINAL   10000.0
#define TEMP_NOMINAL  25.0
#define SERIES_RESISTOR 10000.0

void SensorManager::begin() {
  pinMode(PIN_NTC, INPUT);
}

void SensorManager::update() {
  int adc = analogRead(PIN_NTC);
  float resistance = SERIES_RESISTOR / ((1023.0 / adc) - 1.0);

  float steinhart;
  steinhart = resistance / NTC_NOMINAL;          // (R/Ro)
  steinhart = log(steinhart);                    // ln(R/Ro)
  steinhart /= NTC_BETA;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMP_NOMINAL + 273.15);    // + (1/To)
  steinhart = 1.0 / steinhart;                   // Invert
  steinhart -= 273.15;                           // Convert to °C

  currentTemp = steinhart;
}

float SensorManager::getEvapTemperature() {
  return currentTemp;
}

float SensorManager::getTargetTemperature() {
  return pot.readMapped();
}