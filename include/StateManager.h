#ifndef STATEMANAGER_H
#define STATEMANAGER_H

enum ErrorCode {
    ERROR_NONE,
    ERROR_SENSOR_FAIL
};

class StateManager {
public:
    StateManager();
    void setFreeze(bool state);
    void setFast(bool state);
    void setError(ErrorCode code);

    bool isFreeze();
    bool isFast();
    bool hasError();
    ErrorCode getError();

private:
    bool freezeMode;
    bool fastMode;
    ErrorCode errorCode;
};

#endif