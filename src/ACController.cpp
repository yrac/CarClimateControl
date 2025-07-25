#include "ACController.h"
#include "DisplayManager.h"
#include "SensorManager.h"
#include "MenuSystem.h"
#include "EEPROMManager.h"
#include "CompressorLogic.h"
#include "BuzzerManager.h"

DisplayManager display;
SensorManager sensors;
MenuSystem menu;
EEPROMManager eeprom;
CompressorLogic compressor;
BuzzerManager buzzer;

void ACController::begin() {
  sensors.begin();
  display.begin();
  menu.begin();
  eeprom.begin();
  compressor.begin();
  buzzer.begin();
  display.showInit();
}

void ACController::update() {
  sensors.update();
  menu.update(sensors);
  compressor.update(sensors, menu, eeprom);
  display.update(sensors, menu, compressor);
  buzzer.update(compressor);
}
