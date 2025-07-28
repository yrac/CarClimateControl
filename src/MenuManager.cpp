#include "MenuManager.h"

MenuManager::MenuManager(int buttonPin) {
    _pin = buttonPin;
    _pressStart = 0;
    _buttonStateLast = false;
    _freezeTriggered = false;
    _state = MENU_IDLE;
    _loConfirmed = false;
    _hiConfirmed = false;
}

void MenuManager::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

bool MenuManager::readButton() {
    return digitalRead(_pin) == LOW;
}

void MenuManager::loop() {
    bool buttonState = readButton();

    if (buttonState && !_buttonStateLast) {
        // Button just pressed
        _pressStart = millis();
    } else if (!buttonState && _buttonStateLast) {
        // Button just released
        unsigned long pressDuration = millis() - _pressStart;

        if (pressDuration < 1000) {
            // Short press
            if (_state == MENU_IDLE) {
                _freezeTriggered = true;
            } else if (_state == MENU_CAL_LO) {
                _loConfirmed = true;
                _state = MENU_CAL_HI;
            } else if (_state == MENU_CAL_HI) {
                _hiConfirmed = true;
                _state = MENU_CAL_DONE;
            }
        } else if (pressDuration >= 1000) {
            // Long press → Masuk mode kalibrasi
            _state = MENU_CAL_LO;
            _loConfirmed = false;
            _hiConfirmed = false;
        }
    }

    _buttonStateLast = buttonState;
}

bool MenuManager::isFreezeTriggered() {
    if (_freezeTriggered) {
        _freezeTriggered = false;
        return true;
    }
    return false;
}

bool MenuManager::isInCalibration() {
    return _state == MENU_CAL_LO || _state == MENU_CAL_HI;
}

MenuState MenuManager::getState() {
    return _state;
}

bool MenuManager::isLOConfirmed() {
    return _loConfirmed;
}

bool MenuManager::isHIConfirmed() {
    return _hiConfirmed;
}

bool MenuManager::isCalibrationDone() {
    return _state == MENU_CAL_DONE;
}