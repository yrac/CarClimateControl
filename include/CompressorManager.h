#ifndef COMPRESSORMANAGER_H
#define COMPRESSORMANAGER_H

#include "TempSensor.h"
#include "Potentiometer.h"

enum CompressorState {
    COMP_OFF,
    COMP_ON,
    COMP_HOLD
};

class CompressorManager {
public:
    /**
     * @brief Konstruktor, inisialisasi pin output kompresor
     */
    CompressorManager(int outputPin);

    /**
     * @brief Inisialisasi pin dan status awal
     */
    void begin();

    /**
     * @brief Logika utama kontrol kompresor
     * @param currentTemp Suhu aktual
     * @param targetTemp Suhu target
     * @param freezeActive Mode freeze cleaning aktif
     * @param fastCooling Mode fast cooling aktif
     */
    void loop(float currentTemp, float targetTemp, bool freezeActive, bool fastCooling);

    /**
     * @brief Ambil status kompresor
     */
    CompressorState getState();

    /**
     * @brief Set izin dari ECU
     */
    void setECUAllowed(bool allowed);

    /**
     * @brief Set bypass ECU
     */
    void setBypassECU(bool bypass);

    /**
     * @brief Cek status bypass ECU
     */
    bool isBypassECU() const;

    /**
     * @brief Ambil total jam operasi kompresor
     */
    unsigned long getOperationHours() const;

    /**
     * @brief Reset jam operasi kompresor
     */
    void resetOperationHours();

    /**
     * @brief Set target adaptif untuk adaptive cooling
     */
    void setAdaptiveTarget(float adaptiveTarget);

    /**
     * @brief Set kode error
     */
    void setErrorState(int errorCode);

    /**
     * @brief Ambil kode error
     */
    int getErrorState() const;

private:
    int _pin;
    CompressorState _state;
    unsigned long _lastSwitchTime;
    unsigned long _minOnTime;
    unsigned long _minOffTime;
    bool _ecuAllowed;      // Status izin dari ECU
    bool _bypassECU;       // Status bypass ECU
    unsigned long _operationHours; // Total jam operasi
    float _adaptiveTarget; // Target suhu adaptif
    int _errorState;       // Kode error

    void turnOn();
    void turnOff();
    void updateOperationHours(); // Update jam operasi
};

#endif