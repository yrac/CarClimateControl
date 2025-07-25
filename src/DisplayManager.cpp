#include "DisplayManager.h"
#include "TM1637Display.h"
#include "PinConfig.h"

TM1637Display display(PIN_DISP_CLK, PIN_DISP_DIO);

static uint8_t mapChar(char c) {
  switch (toupper(c)) {
    case 'A': return display.encodeDigit(10);
    case 'B': return display.encodeDigit(11);
    case 'C': return display.encodeDigit(12);
    case 'D': return display.encodeDigit(13);
    case 'E': return display.encodeDigit(14);
    case 'F': return display.encodeDigit(15);
    case 'L': return 0x38;
    case 'O': return display.encodeDigit(0);
    case 'H': return 0x76;
    case 'P': return 0x73;
    case 'U': return 0x3E;
    case 'T': return 0x78;
    case 'W': return 0x3F;
    case 'I': return 0x06;
    case 'N': return 0x37;
    case 'R': return 0x50;
    default: return 0x00;
  }
}

void DisplayManager::begin() {
  display.setBrightness(0x0f);
  display.clear();
}

void DisplayManager::update() {
  // Untuk animasi scroll/efek tambahan nanti
}

void DisplayManager::showTemperature(float temp) {
  int t = round(temp * 10); // Misalnya 26.5 → 265

  uint8_t data[] = {
    display.encodeDigit((t / 100) % 10),
    display.encodeDigit((t / 10) % 10) | 0x80, // titik desimal
    display.encodeDigit(t % 10),
    mapChar('C')  // °C
  };
  display.setSegments(data);
}

void DisplayManager::showWord(const char* word) {
  uint8_t data[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4 && word[i]; i++) {
    data[i] = mapChar(word[i]);
  }
  display.setSegments(data);
}

void DisplayManager::showOperationHour(uint16_t hour) {
  // Misalnya 123 jam → "0123"
  uint8_t data[] = {
    display.encodeDigit((hour / 1000) % 10),
    display.encodeDigit((hour / 100) % 10),
    display.encodeDigit((hour / 10) % 10),
    display.encodeDigit(hour % 10)
  };
  display.setSegments(data);
}