#ifndef POT_CALIBRATION_MANAGER_H
#define POT_CALIBRATION_MANAGER_H

class PotCalibrationManager {
public:
  void begin();
  void calibrate(); // Prosedur kalibrasi manual
  int readRaw();
  float readMapped(); // 5°C to 18°C
};

#endif