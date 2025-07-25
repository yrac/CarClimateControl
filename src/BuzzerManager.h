#ifndef BUZZER_MANAGER_H
#define BUZZER_MANAGER_H

#include "CompressorLogic.h"

class BuzzerManager {
public:
  void begin();
  void update(CompressorLogic& logic);
};

#endif // BUZZER_MANAGER_H
