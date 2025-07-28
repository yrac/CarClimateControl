#ifndef FANMANAGER_H
#define FANMANAGER_H

enum FanState {
    FAN_OFF,
    FAN_ON
};

class FanManager {
public:
    FanManager(int outputPin);
    void begin();
    void turnOn();
    void turnOff();
    void loop(bool compressorActive, bool fastCooling);
    FanState getState();

private:
    int _pin;
    FanState _state;
};

#endif