#include "EEPROMManager.h"
#include <EEPROM.h>

void EEPROMManager::begin() {
    // Kosong untuk sekarang (bisa ditambah validasi data)
}

void EEPROMManager::saveCalibration(int lo, int hi) {
    EEPROM.put(addrLo, lo);
    EEPROM.put(addrHi, hi);
}

void EEPROMManager::loadCalibration(int &lo, int &hi) {
    EEPROM.get(addrLo, lo);
    EEPROM.get(addrHi, hi);

    // Validasi sederhana
    if (lo < 0 || lo > 1023 || hi < 0 || hi > 1023 || lo >= hi) {
        lo = 0;
        hi = 1023;
    }
}