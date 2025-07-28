#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

class EEPROMManager {
public:
    void begin();
    void saveCalibration(int lo, int hi);
    void loadCalibration(int &lo, int &hi);

private:
    const int addrLo = 0;
    const int addrHi = 2;
};

#endif