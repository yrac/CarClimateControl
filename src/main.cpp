#include <Arduino.h>
#include <TM1637Display.h>
#include <math.h>

// === Pin Assignment ===
#define potPin A0
#define ntcPin A1

#define relayAC 8
#define relayBlowerCut 7
#define blowerSpeed4 6

#define freezeBtnPin 5
#define acRequestPin 9
#define acPermissionPin 10
#define bypassSwitchPin 11

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

// === NTC Constants ===
const float seriesResistor = 10000.0;
const float nominalResistance = 10000.0;
const float nominalTemp = 25.0;
const float bCoefficient = 3950.0;
const int adcMax = 1023;

// === Status Flags ===
float hysteresis = 1.0;
bool freezeMode = false;
bool freezeDone = false;
unsigned long potMovedTime = 0;
int lastPotRaw = 0;
bool showingSetpoint = false;

// === Fungsi Baca Suhu ===
float readNTCTemperature()
{
  int analogValue = analogRead(ntcPin);
  float voltage = analogValue * (5.0 / adcMax);
  float resistance = (5.0 / voltage - 1.0) * seriesResistor;
  float tempK = 1.0 / (1.0 / (nominalTemp + 273.15) + log(resistance / nominalResistance) / bCoefficient);
  return tempK - 273.15;
}

float readSetpoint()
{
  return map(analogRead(potPin), 0, 1023, 50, 180) / 10.0;
}

// === Tampilkan Kata (4 Huruf) ===
void displayWord(const char *w)
{
  uint8_t seg[4] = {0};

  for (int i = 0; i < 4 && w[i] != '\0'; i++)
  {
    switch (w[i])
    {
    case 'A':
      seg[i] = 0b01110111;
      break;
    case 'C':
      seg[i] = 0b00111001;
      break;
    case 'E':
      seg[i] = 0b01111001;
      break;
    case 'I':
      seg[i] = 0b00000110;
      break;
    case 'L':
      seg[i] = 0b00111000;
      break;
    case 'N':
      seg[i] = 0b01010100;
      break;
    case 'O':
      seg[i] = 0b00111111;
      break;
    case 'P':
      seg[i] = 0b01110011;
      break;
    case 'T':
      seg[i] = 0b01111000;
      break;
    case 'U':
      seg[i] = 0b00111110;
      break;
    case 'W':
      seg[i] = 0b00111110;
      break; // mirip U
    default:
      seg[i] = 0x00;
      break; // blank
    }
  }

  display.setSegments(seg);
}

// === Tampilkan Suhu dengan °C ===
void displayTempWithC(int temp)
{
  uint8_t data[] = {
      display.encodeDigit((temp / 10) % 10),
      display.encodeDigit(temp % 10),
      0b01100011, // derajat °
      0b00111001  // huruf C
  };
  display.setSegments(data);
}

void setup()
{
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

  display.setBrightness(7);
  displayWord("INIT");
  delay(2000);

  Serial.begin(9600);
}

void loop()
{
  float evapTemp = readNTCTemperature();
  float setpoint = readSetpoint();
  int evapTempInt = (int)evapTemp;
  int setTempInt = (int)setpoint;
  int potRaw = analogRead(potPin);

  if (abs(potRaw - lastPotRaw) > 5)
  {
    potMovedTime = millis();
    showingSetpoint = true;
    lastPotRaw = potRaw;
  }

  if (digitalRead(freezeBtnPin) == LOW && !freezeMode && !freezeDone)
  {
    freezeMode = true;
    freezeDone = false;
    Serial.println("Freeze cleaning activated");
  }

  bool needAC = false;
  if (freezeMode)
  {
    needAC = (evapTemp > -5.0);
  }
  else if (!freezeDone)
  {
    needAC = (evapTemp > setpoint + hysteresis);
  }

  digitalWrite(acRequestPin, needAC ? LOW : HIGH);

  bool acPermission = (digitalRead(acPermissionPin) == LOW);
  bool bypassMode = (digitalRead(bypassSwitchPin) == LOW);

  if (needAC && (acPermission || bypassMode))
  {
    digitalWrite(relayAC, LOW);
  }
  else
  {
    digitalWrite(relayAC, HIGH);
  }

  if (freezeMode)
  {
    digitalWrite(relayBlowerCut, HIGH);
    digitalWrite(blowerSpeed4, LOW);
    if (evapTemp <= -5.0)
    {
      freezeMode = false;
      freezeDone = true;
      digitalWrite(blowerSpeed4, HIGH);
    }
  }
  else
  {
    digitalWrite(relayBlowerCut, LOW);
    digitalWrite(blowerSpeed4, LOW);
  }

  if (freezeMode)
  {
    displayWord("COOL");
  }
  else if (needAC && !acPermission && !bypassMode)
  {
    displayWord("WAIT");
  }
  else if (showingSetpoint)
  {
    displayTempWithC(setTempInt);
    if (millis() - potMovedTime > 3000)
    {
      showingSetpoint = false;
    }
  }
  else
  {
    displayTempWithC(evapTempInt);
  }

  Serial.print("Evap: ");
  Serial.print(evapTemp);
  Serial.print(" | Set: ");
  Serial.print(setpoint);
  Serial.print(" | Req: ");
  Serial.print(needAC);
  Serial.print(" | Perm: ");
  Serial.print(acPermission);
  Serial.print(" | Bypass: ");
  Serial.print(bypassMode);
  Serial.print(" | Comp: ");
  Serial.println(digitalRead(relayAC) == LOW ? "ON" : "OFF");

  delay(500);
}
