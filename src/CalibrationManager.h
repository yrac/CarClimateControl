#ifndef CALIBRATION_MANAGER_H
#define CALIBRATION_MANAGER_H

class CalibrationManager {
public:
  void begin();
  void update();
  bool isCalibrating();

private:
  enum CalState {
    CAL_IDLE,
    CAL_WAIT_LO,
    CAL_WAIT_HI,
    CAL_DONE
  };

  CalState state = CAL_IDLE;
  unsigned long lastDisplayUpdate = 0;
};

#endif