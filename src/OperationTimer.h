#ifndef OPERATION_TIMER_H
#define OPERATION_TIMER_H

class OperationTimer {
public:
  void begin();
  void update(bool compressorOn);

  uint16_t getHours();
  void reset();
};

#endif