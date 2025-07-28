#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TempSensor {
public:
    TempSensor(int pin);
    float readTemperature(); // Celcius

private:
    int _pin;
    float readADC();
};

#endif