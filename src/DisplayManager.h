#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>

class DisplayManager {
public:
  void begin();
  void update();

  void showTemperature(float temp);     // Tampilkan suhu
  void showWord(const char* word);      // Tampilkan teks pendek (seperti "WAIT", "CAL ")
  void showOperationHour(uint16_t hour);
};

#endif