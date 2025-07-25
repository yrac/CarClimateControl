#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

enum MenuState {
  MENU_NONE,
  MENU_CALIBRATE,
  MENU_VIEW_OPH,
  MENU_RESET_OPH,
  MENU_BYPASS_TOGGLE,
  MENU_EXIT
};

class MenuManager {
public:
  void begin();
  void update();
  bool inCalibrationMode();
  void handleButton(bool shortPress, bool longPress);
  void enter();
  bool inMenu();
};

#endif