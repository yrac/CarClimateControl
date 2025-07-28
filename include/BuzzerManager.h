#ifndef BUZZERMANAGER_H
#define BUZZERMANAGER_H

class BuzzerManager {
public:
    BuzzerManager(int pin);
    void beep(int duration = 100);
    void loop();  // untuk handle timing non-blocking

private:
    int _pin;
    unsigned long _beepUntil;
};

#endif