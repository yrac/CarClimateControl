#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer {
public:
    Potentiometer(int pin);
    void calibrate(int lo, int hi);
    void setCalibrationPoints(int rawLo, int rawHi);
    int getRawValue();           // Nilai ADC mentah
    float getNormalized();       // 0.0 - 1.0
    float getTargetTemperature(float minTemp, float maxTemp); // Konversi ke suhu

private:
    int _pin;
    int _rawLo;
    int _rawHi;
};

#endif