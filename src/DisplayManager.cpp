#include "DisplayManager.h"

DisplayManager::DisplayManager() : _display(2, 3) {}

void DisplayManager::begin() {
  _display.setBrightness(7);
}

void DisplayManager::showInit() {
  showWord("INIT");
  delay(2000);
}

void DisplayManager::showWord(const char* w) {
  uint8_t seg[4] = {0};
  for (int i = 0; i < 4 && w[i] != '\0'; i++) {
    switch (w[i]) {
      case 'A': seg[i] = 0b01110111; break;
      case 'C': seg[i] = 0b00111001; break;
      case 'E': seg[i] = 0b01111001; break;
      case 'I': seg[i] = 0b00000110; break;
      case 'L': seg[i] = 0b00111000; break;
      case 'N': seg[i] = 0b01010100; break;
      case 'O': seg[i] = 0b00111111; break;
      case 'P': seg[i] = 0b01110011; break;
      case 'T': seg[i] = 0b01111000; break;
      case 'U': seg[i] = 0b00111110; break;
      case 'W': seg[i] = 0b00111110; break;
      default: seg[i] = 0x00; break;
    }
  }
  _display.setSegments(seg);
}

void DisplayManager::showTempWithC(int temp) {
  uint8_t data[] = {
    _display.encodeDigit((temp / 10) % 10),
    _display.encodeDigit(temp % 10),
    0b01100011,
    0b00111001
  };
  _display.setSegments(data);
}