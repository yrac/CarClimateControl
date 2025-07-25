#include "CompressorManager.h"
#include "PinConfig.h"
#include "EEPROMManager.h"

extern EEPROMManager config;

#define ECU_TIMEOUT_MS 5000  // 5 detik

void CompressorManager::begin() {
  pinMode(PIN_COMPRESSOR_RELAY, OUTPUT);
  digitalWrite(PIN_COMPRESSOR_RELAY, LOW);

  pinMode(PIN_COMPRESSOR_ECU_IN, OUTPUT);     // ke ECU (request)
  pinMode(PIN_COMPRESSOR_ECU_FEEDBACK, INPUT); // dari ECU (izin)
}

void CompressorManager::update(bool requestCooling) {
  // Kirim sinyal request ke ECU
  if (requestCooling) {
    digitalWrite(PIN_COMPRESSOR_ECU_IN, LOW); // Aktif low
    ecuRequestTime = millis();
  } else {
    digitalWrite(PIN_COMPRESSOR_ECU_IN, HIGH);
    running = false;
    digitalWrite(PIN_COMPRESSOR_RELAY, LOW);
    return;
  }

  // Cek feedback ECU
  bool ecuGivesPermission = digitalRead(PIN_COMPRESSOR_ECU_FEEDBACK) == LOW;

  if (config.getConfig().bypassMode || ecuGivesPermission) {
    digitalWrite(PIN_COMPRESSOR_RELAY, HIGH);
    running = true;
  } else if (millis() - ecuRequestTime > ECU_TIMEOUT_MS) {
    // Timeout tanpa izin
    running = false;
    digitalWrite(PIN_COMPRESSOR_RELAY, LOW);
  }
}

bool CompressorManager::isRunning() {
  return running;
}

void CompressorManager::forceStop() {
  digitalWrite(PIN_COMPRESSOR_RELAY, LOW);
  running = false;
}