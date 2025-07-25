#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager {
public:
  void begin();
  void update();

  bool isShortPress();
  bool isLongPress();
  bool isPressed(); // Untuk kalibrasi

private:
  bool lastState = false;
  unsigned long pressStart = 0;
  bool shortPressDetected = false;
  bool longPressDetected = false;
};

#endif