#ifndef FAST_COOLING_MANAGER_H
#define FAST_COOLING_MANAGER_H

class FastCoolingManager {
public:
  void begin();
  void update(float actualTemp, float targetTemp);

  bool shouldDelayCompressor();
  bool isActive();

private:
  bool active = false;
};

#endif