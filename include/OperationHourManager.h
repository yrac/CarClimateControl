#ifndef OPERATIONHOURMANAGER_H
#define OPERATIONHOURMANAGER_H

class OperationHourManager {
public:
    OperationHourManager();
    void begin();
    void loop(bool compressorOn);
    unsigned long getHours(); // dalam jam
    unsigned long getMinutes(); // akurat ke menit

private:
    unsigned long _lastOnTime;
    unsigned long _totalMillis;
    bool _wasOn;
};

#endif