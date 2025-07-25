#ifndef TEMP_CONTROLLER_H
#define TEMP_CONTROLLER_H

class TempController {
public:
  void begin();
  void update(float actualTemp);

  float getTargetTemp();
  bool shouldCompressorRun();

private:
  float targetTemp = 12.0; // default
  bool compressorAllowed = false;
};

#endif