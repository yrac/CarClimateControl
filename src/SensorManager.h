#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

class SensorManager {
public:
  void begin();
  void update();

  float getEvapTemperature();   // Suhu aktual evaporator
  float getTargetTemperature(); // Suhu yang diinginkan user
};

#endif