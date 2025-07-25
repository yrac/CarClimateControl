#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

class EEPROMManager {
public:
  void begin();
  void saveSetpoint(int value);
  int loadSetpoint();
};

#endif // EEPROM_MANAGER_H
