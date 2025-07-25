#include "DisplayManager.h"
#include <TM1637Display.h>
#include "PinConfig.h"

static TM1637Display display(PIN_TM1637_CLK, PIN_TM1637_DIO);

static bool overrideDisplay = false;
static unsigned long scrollTimer = 0;
static String scrollText = "";
static int scrollIndex = 0;

void DisplayManager::begin() {
  display.setBrightness(0x0f); // maksimum brightness
  display.clear();
}

void DisplayManager::update() {
  if (!scrollText.isEmpty()) {
    if (millis() - scrollTimer > 400) {
      scrollTimer = millis();
      String view = "    " + scrollText + "    ";
      String part = view.substring(scrollIndex, scrollIndex + 4);
      display.showString(part.c_str());
      scrollIndex++;
      if (scrollIndex > view.length() - 4) {
        scrollIndex = 0;
        scrollText = "";  // stop scroll
      }
    }
  }
}

void DisplayManager::showTemperature(float temp, bool withUnit) {
  overrideDisplay = true;

  uint8_t data[] = {
    display.encodeDigit((int)temp / 10),
    display.encodeDigit((int)temp % 10),
    display.encodePoint(true),
    withUnit ? display.encodeChar('C') : display.encodeDigit(0)
  };
  display.setSegments(data);
}

void DisplayManager::showWord(const char* word) {
  overrideDisplay = true;
  display.showString(word);
}

void DisplayManager::showScroll(const char* text) {
  scrollText = String(text);
  scrollIndex = 0;
  scrollTimer = 0;
}

void DisplayManager::showOphr(uint16_t hours) {
  overrideDisplay = true;
  uint8_t digits[4];
  digits[0] = display.encodeDigit((hours / 1000) % 10);
  digits[1] = display.encodeDigit((hours / 100) % 10);
  digits[2] = display.encodeDigit((hours / 10) % 10);
  digits[3] = display.encodeDigit(hours % 10);
  display.setSegments(digits);
}

void DisplayManager::setOverride(bool enable) {
  overrideDisplay = enable;
}
