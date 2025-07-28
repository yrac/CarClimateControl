#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <Arduino.h>

enum MenuState {
    MENU_IDLE,
    MENU_CAL_LO,
    MENU_CAL_HI,
    MENU_CAL_DONE
};

class MenuManager {
public:
    MenuManager(int buttonPin);
    void begin();
    void loop();
    bool isFreezeTriggered();    // Short press
    bool isInCalibration();
    MenuState getState();
    bool isLOConfirmed();
    bool isHIConfirmed();
    bool isCalibrationDone();

private:
    int _pin;
    unsigned long _pressStart;
    bool _buttonStateLast;
    bool _freezeTriggered;
    MenuState _state;
    bool _loConfirmed;
    bool _hiConfirmed;

    bool readButton();
};

#endif