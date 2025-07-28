#ifndef FREEZECLEANER_H
#define FREEZECLEANER_H

#include <Arduino.h>

enum FreezeState {
    FREEZE_IDLE,
    FREEZE_RUNNING,
    FREEZE_DONE
};

class FreezeCleaner {
public:
    FreezeCleaner();
    void trigger();  // dipanggil saat tombol FREEZE ditekan singkat
    void loop();
    bool isActive();
    FreezeState getState();

private:
    unsigned long _startTime;
    unsigned long _duration;
    FreezeState _state;
};

#endif