#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

class TempSensor {
public:
    void begin();
    float read();
};

#endif