#include "DisplayManager.h"
#include <Arduino.h>

DisplayManager::DisplayManager(int clkPin, int dioPin)
    : display(clkPin, dioPin), currentMode(DISP_IDLE), lastUpdate(0) {}

void DisplayManager::begin() {
    display.setBrightness(0x0f);
    display.clear();
}

void DisplayManager::showTemperature(float tempC) {
    int temp = (int)(tempC * 10); // Misalnya: 23.4°C → 234
    display.showNumberDecEx(temp, 0b01000000, true);
    currentMode = DISP_TEMP;
}

void DisplayManager::showStatus(DisplayMode mode) {
    currentMode = mode;
    switch (mode) {
        case DISP_CAL: showText("CAL"); break;
        case DISP_LO:  showText("LO"); break;
        case DISP_HI:  showText("HI"); break;
        case DISP_OK:  showText("OK"); break;
        case DISP_ERR: showText("ERR"); break;
        case DISP_FAST: showText("FST"); break;
        case DISP_FREEZE: showText("FRE"); break;
        case DISP_IDLE: display.clear(); break;
        default: break;
    }
}

void DisplayManager::showText(const char* txt) {
    // TM1637Display does not have showString, so we use encodeDigit for each char
    uint8_t segs[4] = {0};
    for (int i = 0; i < 4 && txt[i]; ++i) {
        segs[i] = display.encodeDigit(txt[i]);
    }
    display.setSegments(segs);
}

void DisplayManager::loop() {
    // future: blink or animations
}