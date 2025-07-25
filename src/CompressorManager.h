#ifndef COMPRESSOR_MANAGER_H
#define COMPRESSOR_MANAGER_H

class CompressorManager {
public:
  void begin();
  void update(bool requestCooling);

  bool isRunning();
  void forceStop();

private:
  bool running = false;
  unsigned long ecuRequestTime = 0;
};

#endif