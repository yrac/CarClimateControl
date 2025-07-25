#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

class SensorManager {
public:
  void begin();
  void update();
  float getCurrentTemperature();
  int getSetpoint();
};

#endif // SENSOR_MANAGER_H
