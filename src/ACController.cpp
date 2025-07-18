#include "ACController.h"
#include <Arduino.h>
#include <math.h>

const float seriesResistor = 10000.0;
const float nominalResistance = 10000.0;
const float nominalTemp = 25.0;
const float bCoefficient = 3950.0;
const int adcMax = 1023;

ACController::ACController(DisplayManager &display) : _display(display) {}

void ACController::begin() {
  pinMode(RELAY_AC_PIN, OUTPUT);
  pinMode(BLOWER_CUT_PIN, OUTPUT);
  pinMode(BLOWER_SPEED4_PIN, OUTPUT);
  pinMode(FREEZE_BTN_PIN, INPUT_PULLUP);
  pinMode(AC_REQUEST_PIN, OUTPUT);
  pinMode(AC_PERMISSION_PIN, INPUT_PULLUP);
  pinMode(BYPASS_SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_AC_PIN, HIGH);
  digitalWrite(BLOWER_CUT_PIN, LOW);
  digitalWrite(BLOWER_SPEED4_PIN, LOW);
  digitalWrite(AC_REQUEST_PIN, HIGH);

  _display.begin();
  _display.showInit();

  Serial.begin(9600);
}

float ACController::readNTC() {
  int val = analogRead(NTC_PIN);
  float voltage = val * (5.0 / adcMax);
  float resistance = (5.0 / voltage - 1.0) * seriesResistor;
  float tempK = 1.0 / (1.0 / (nominalTemp + 273.15) + log(resistance / nominalResistance) / bCoefficient);
  return tempK - 273.15;
}

float ACController::readSetpoint() {
  return map(analogRead(POT_PIN), 0, 1023, 50, 180) / 10.0;
}

void ACController::update() {
  float evapTemp = readNTC();
  float setpoint = readSetpoint();
  int evapInt = (int)evapTemp;
  int setInt = (int)setpoint;
  int potRaw = analogRead(POT_PIN);

  if (abs(potRaw - lastPotRaw) > 5) {
    potMovedTime = millis();
    showingSetpoint = true;
    lastPotRaw = potRaw;
  }

  if (digitalRead(FREEZE_BTN_PIN) == LOW && !freezeMode && !freezeDone) {
    freezeMode = true;
    freezeDone = false;
  }

  bool needAC = false;
  if (freezeMode) needAC = (evapTemp > -5.0);
  else if (!freezeDone) needAC = (evapTemp > setpoint + hysteresis);

  digitalWrite(AC_REQUEST_PIN, needAC ? LOW : HIGH);
  bool acPermission = digitalRead(AC_PERMISSION_PIN) == LOW;
  bool bypassMode = digitalRead(BYPASS_SWITCH_PIN) == LOW;

  if (needAC && (acPermission || bypassMode)) digitalWrite(RELAY_AC_PIN, LOW);
  else digitalWrite(RELAY_AC_PIN, HIGH);

  if (freezeMode) {
    digitalWrite(BLOWER_CUT_PIN, HIGH);
    digitalWrite(BLOWER_SPEED4_PIN, LOW);
    if (evapTemp <= -5.0) {
      freezeMode = false;
      freezeDone = true;
      digitalWrite(BLOWER_SPEED4_PIN, HIGH);
    }
  } else {
    digitalWrite(BLOWER_CUT_PIN, LOW);
    digitalWrite(BLOWER_SPEED4_PIN, LOW);
  }

  if (freezeMode) _display.showWord("COOL");
  else if (needAC && !acPermission && !bypassMode) _display.showWord("WAIT");
  else if (showingSetpoint) {
    _display.showTempWithC(setInt);
    if (millis() - potMovedTime > 3000) showingSetpoint = false;
  } else {
    _display.showTempWithC(evapInt);
  }

  Serial.print("Evap: "); Serial.print(evapTemp);
  Serial.print(" | Set: "); Serial.print(setpoint);
  Serial.print(" | Req: "); Serial.print(needAC);
  Serial.print(" | Perm: "); Serial.print(acPermission);
  Serial.print(" | Bypass: "); Serial.print(bypassMode);
  Serial.print(" | Comp: "); Serial.println(digitalRead(RELAY_AC_PIN) == LOW ? "ON" : "OFF");
}