#include "ACController.h"
#include "PinConfig.h"

ACController::ACController()
    : tempSensor(NTC_PIN),
      potentiometer(POT_PIN),
      display(TM1637_CLK_PIN, TM1637_DIO_PIN),
      buzzer(RELAY_BLOWER_CUT),
      compressor(RELAY_COMPRESSOR),
      fan(RELAY_BLOWER_4),
      menu(FREEZE_BTN_PIN)
{
    calLo = 0;
    calHi = 1023;
    lastDisplayUpdate = 0;
}

void ACController::begin() {
    display.begin();
    menu.begin();
    compressor.begin();
    fan.begin();
    eeprom.begin();
    hourCounter.begin();

    eeprom.loadCalibration(calLo, calHi);
    potentiometer.setCalibrationPoints(calLo, calHi);
}

void ACController::loop() {
    menu.loop();
    freezeCleaner.loop();
    buzzer.loop();

    float currentTemp = tempSensor.readTemperature();
    float targetTemp = potentiometer.getTargetTemperature(18.0, 28.0);

    // Error detection
    if (isnan(currentTemp) || currentTemp < -10 || currentTemp > 70) {
        state.setError(ERROR_SENSOR_FAIL);
    } else {
        state.setError(ERROR_NONE);
    }

    // Handle freeze-cleaning trigger
    if (menu.isFreezeTriggered()) {
        freezeCleaner.trigger();
        state.setFreeze(true);
        buzzer.beep(100);
    }

    // Handle calibration mode
    if (menu.isInCalibration()) {
        handleCalibration();
    }

    // Logic control
    bool freeze = freezeCleaner.isActive();
    bool fast = state.isFast();

    compressor.loop(currentTemp, targetTemp, freeze, fast);
    fan.loop(compressor.getState() == COMP_ON, fast);
    hourCounter.loop(compressor.getState() == COMP_ON);

    updateDisplay(currentTemp);
}

void ACController::handleCalibration() {
    switch (menu.getState()) {
        case MENU_CAL_LO:
            display.showStatus(DISP_LO);
            if (menu.isLOConfirmed()) {
                calLo = potentiometer.getRawValue();
                buzzer.beep(100);
            }
            break;
        case MENU_CAL_HI:
            display.showStatus(DISP_HI);
            if (menu.isHIConfirmed()) {
                calHi = potentiometer.getRawValue();
                buzzer.beep(100);
            }
            break;
        case MENU_CAL_DONE:
            eeprom.saveCalibration(calLo, calHi);
            potentiometer.setCalibrationPoints(calLo, calHi);
            display.showStatus(DISP_OK);
            buzzer.beep(200);
            break;
        default: break;
    }
}

void ACController::updateDisplay(float currentTemp) {
    if (state.hasError()) {
        display.showStatus(DISP_ERR);
    } else if (state.isFreeze()) {
        display.showStatus(DISP_FREEZE);
    } else if (state.isFast()) {
        display.showStatus(DISP_FAST);
    } else {
        // Update suhu setiap 500 ms
        if (millis() - lastDisplayUpdate > 500) {
            display.showTemperature(currentTemp);
            lastDisplayUpdate = millis();
        }
    }
}