#ifndef BUZZER_MANAGER_H
#define BUZZER_MANAGER_H

enum BeepType {
  BEEP_SHORT,
  BEEP_LONG,
  BEEP_DOUBLE,
  BEEP_PERSISTENT,
  BEEP_NONE
};

class BuzzerManager {
public:
  void begin();
  void update();

  void beep(BeepType type);
  void beepPersistent();
  void stop();

private:
  BeepType currentBeep = BEEP_NONE;
  unsigned long beepStart = 0;
  bool buzzerState = false;
};

#endif