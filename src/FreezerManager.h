#ifndef FREEZER_MANAGER_H
#define FREEZER_MANAGER_H

class FreezerManager {
public:
  void begin();
  void update(float currentTemp);

  void start();
  bool isRunning();

private:
  enum FreezeState {
    FREEZE_IDLE,
    FREEZE_COMPRESSOR_ON,
    FREEZE_REACHED_TARGET,
    FREEZE_BLOWER_ON
  };

  FreezeState state = FREEZE_IDLE;
  unsigned long stateStartTime = 0;
};

#endif