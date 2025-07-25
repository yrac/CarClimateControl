#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

enum ErrorCode {
  ERR_NONE,
  ERR_SENSOR_DISCONNECTED,
  ERR_SENSOR_RANGE,
  ERR_EEPROM_CORRUPT
};

class ErrorManager {
public:
  void begin();
  void update();

  ErrorCode getError();
  const char* getErrorText();
  bool hasError();
};

#endif