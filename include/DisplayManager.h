#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <TM1637Display.h>

enum DisplayMode {
    DISP_TEMP,
    DISP_CAL,
    DISP_LO,
    DISP_HI,
    DISP_OK,
    DISP_ERR,
    DISP_FAST,
    DISP_FREEZE,
    DISP_IDLE
};

class DisplayManager {
public:
    DisplayManager(int clkPin, int dioPin);
    void begin();
    void showTemperature(float tempC);
    void showStatus(DisplayMode mode);
    void loop();

private:
    TM1637Display display;
    DisplayMode currentMode;
    unsigned long lastUpdate;
    void showText(const char* txt);
};

#endif