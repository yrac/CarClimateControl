#include "ACController.h"
#include <Arduino.h>
#include <math.h>

#define potPin A0
#define ntcPin A1
#define relayAC 8
#define relayBlowerCut 7
#define blowerSpeed4 6
#define freezeBtnPin 5
#define acRequestPin 9
#define acPermissionPin 10
#define bypassSwitchPin 11

const float seriesResistor = 10000.0;
const float nominalResistance = 10000.0;
const float nominalTemp = 25.0;
const float bCoefficient = 3950.0;
const int adcMax = 1023;

ACController::ACController(DisplayManager &display) : _display(display) {}

void ACController::begin() {
  pinMode(relayAC, OUTPUT);
  pinMode(relayBlowerCut, OUTPUT);
  pinMode(blowerSpeed4, OUTPUT);
  pinMode(freezeBtnPin, INPUT_PULLUP);
  pinMode(acRequestPin, OUTPUT);
  pinMode(acPermissionPin, INPUT_PULLUP);
  pinMode(bypassSwitchPin, INPUT_PULLUP);

  digitalWrite(relayAC, HIGH);
  digitalWrite(relayBlowerCut, LOW);
  digitalWrite(blowerSpeed4, LOW);
  digitalWrite(acRequestPin, HIGH);

  _display.begin();
  _display.showInit();

  Serial.begin(9600);
}

float ACController::readNTC() {
  int val = analogRead(ntcPin);
  float voltage = val * (5.0 / adcMax);
  float resistance = (5.0 / voltage - 1.0) * seriesResistor;
  float tempK = 1.0 / (1.0 / (nominalTemp + 273.15) + log(resistance / nominalResistance) / bCoefficient);
  return tempK - 273.15;
}

float ACController::readSetpoint() {
  return map(analogRead(potPin), 0, 1023, 50, 180) / 10.0;
}

void ACController::update() {
  float evapTemp = readNTC();
  float setpoint = readSetpoint();
  int evapInt = (int)evapTemp;
  int setInt = (int)setpoint;
  int potRaw = analogRead(potPin);

  if (abs(potRaw - lastPotRaw) > 5) {
    potMovedTime = millis();
    showingSetpoint = true;
    lastPotRaw = potRaw;
  }

  if (digitalRead(freezeBtnPin) == LOW && !freezeMode && !freezeDone) {
    freezeMode = true;
    freezeDone = false;
  }

  bool needAC = false;
  if (freezeMode) needAC = (evapTemp > -5.0);
  else if (!freezeDone) needAC = (evapTemp > setpoint + hysteresis);

  digitalWrite(acRequestPin, needAC ? LOW : HIGH);
  bool acPermission = digitalRead(acPermissionPin) == LOW;
  bool bypassMode = digitalRead(bypassSwitchPin) == LOW;

  if (needAC && (acPermission || bypassMode)) digitalWrite(relayAC, LOW);
  else digitalWrite(relayAC, HIGH);

  if (freezeMode) {
    digitalWrite(relayBlowerCut, HIGH);
    digitalWrite(blowerSpeed4, LOW);
    if (evapTemp <= -5.0) {
      freezeMode = false;
      freezeDone = true;
      digitalWrite(blowerSpeed4, HIGH);
    }
  } else {
    digitalWrite(relayBlowerCut, LOW);
    digitalWrite(blowerSpeed4, LOW);
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
  Serial.print(" | Comp: "); Serial.println(digitalRead(relayAC) == LOW ? "ON" : "OFF");
}