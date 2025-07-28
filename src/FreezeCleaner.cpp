#include "FreezeCleaner.h"

FreezeCleaner::FreezeCleaner() {
    _startTime = 0;
    _duration = 10000; // 10 detik cleaning
    _state = FREEZE_IDLE;
}

void FreezeCleaner::trigger() {
    _startTime = millis();
    _state = FREEZE_RUNNING;
}

void FreezeCleaner::loop() {
    if (_state == FREEZE_RUNNING && millis() - _startTime >= _duration) {
        _state = FREEZE_DONE;
    }
}

bool FreezeCleaner::isActive() {
    return _state == FREEZE_RUNNING;
}

FreezeState FreezeCleaner::getState() {
    return _state;
}