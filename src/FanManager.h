#ifndef FAN_MANAGER_H
#define FAN_MANAGER_H

enum FanMode {
  FAN_OFF,
  FAN_LOW,
  FAN_MED,
  FAN_HIGH,
  FAN_FULL // mode force 100% (bypass resistor)
};

class FanManager {
public:
  void begin();
  void update();

  void setMode(FanMode mode);
  FanMode getMode();

private:
  FanMode currentMode = FAN_OFF;
};

#endif