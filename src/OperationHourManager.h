#ifndef OPERATION_HOUR_MANAGER_H
#define OPERATION_HOUR_MANAGER_H

class OperationHourManager {
public:
  void begin();
  void update(bool compressorActive);

  uint16_t getHour();     // Total jam
  void reset();           // Reset ke 0
  bool needsService();    // Apakah sudah waktunya servis?
};

#endif