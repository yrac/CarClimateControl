#include "ACController.h"
#include "TempSensor.h"
#include "TempController.h"
#include "CompressorManager.h"
#include "FanManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "MenuManager.h"
#include "CalibrationManager.h"
#include "EEPROMManager.h"
#include "OperationHourManager.h"
#include "FreezerManager.h"
#include "FastCoolingManager.h"
#include "ErrorManager.h"
#include "BuzzerManager.h"

TempSensor tempSensor;
TempController tempController;
CompressorManager compressor;
FanManager fan;
DisplayManager display;
InputManager input;
MenuManager menu;
CalibrationManager calibration;
EEPROMManager config;
OperationHourManager ophr;
FreezerManager freezer;
FastCoolingManager fastCooling;
ErrorManager error;
BuzzerManager buzzer;

void ACController::begin() {
  config.begin();
  display.begin();
  buzzer.begin();
  tempSensor.begin();
  tempController.begin();
  compressor.begin();
  fan.begin();
  input.begin();
  menu.begin();
  calibration.begin();
  ophr.begin();
  freezer.begin();
  fastCooling.begin();
  error.begin();

  display.showWord("INIT");
  delay(2000);
}

void ACController::update() {
  input.update();

  // Tombol lama → masuk menu
  if (input.isLongPress()) {
    menu.enter();
  }

  // Mode kalibrasi
  if (menu.inCalibrationMode()) {
    calibration.update();
    return;
  }

  // Update suhu
  float actualTemp = tempSensor.read();
  tempController.update(actualTemp);
  float targetTemp = tempController.getTargetTemp();

  // Error handling
  error.update(actualTemp);
  if (error.hasError()) {
    display.showWord(error.getErrorCode());
    buzzer.beep(BEEP_ERROR);
    compressor.forceStop();
    fan.setMode(FAN_OFF);
    return;
  }

  // Freeze cleaning
  if (input.isShortPress() && !freezer.isRunning()) {
    freezer.start();
  }
  freezer.update(actualTemp);
  if (freezer.isRunning()) return;

  // Fast cooling logic
  fastCooling.update(actualTemp, targetTemp);

  // Kompresor logic
  bool allowCompressor = tempController.shouldCompressorRun() && !fastCooling.shouldDelayCompressor();
  compressor.update(allowCompressor);

  // Fan control
  if (fastCooling.isActive()) {
    fan.setMode(FAN_HIGH);
  } else if (compressor.isRunning()) {
    fan.setMode(FAN_MEDIUM);
  } else {
    fan.setMode(FAN_LOW);
  }

  // Operation hour tracking
  ophr.update(compressor.isRunning());

  // Display
  if (menu.inMenu()) {
    menu.update();
  } else if (millis() - menu.getLastPotMoveTime() < 3000) {
    display.showTemperature(targetTemp);
  } else {
    display.showTemperature(actualTemp);
  }
}