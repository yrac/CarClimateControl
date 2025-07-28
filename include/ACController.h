#ifndef ACCONTROLLER_H
#define ACCONTROLLER_H

#include "TempSensor.h"
#include "Potentiometer.h"
#include "DisplayManager.h"
#include "BuzzerManager.h"
#include "CompressorManager.h"
#include "FanManager.h"
#include "FreezeCleaner.h"
#include "MenuManager.h"
#include "EEPROMManager.h"
#include "OperationHourManager.h"
#include "StateManager.h"

class ACController {
public:
    ACController();
    void begin();
    void loop();

private:
    TempSensor tempSensor;
    Potentiometer potentiometer;
    DisplayManager display;
    BuzzerManager buzzer;
    CompressorManager compressor;
    FanManager fan;
    FreezeCleaner freezeCleaner;
    MenuManager menu;
    EEPROMManager eeprom;
    OperationHourManager hourCounter;
    StateManager state;

    int calLo, calHi;
    unsigned long lastDisplayUpdate;

    void handleCalibration();
    void updateDisplay(float currentTemp);
};

#endif