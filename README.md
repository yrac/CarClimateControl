# 🚗 Arduino Car AC Controller

**Simple Automotive Climate Control System** using Arduino (Uno or Mega) with TM1637 display, NTC temperature sensor, and ECU integration (Speeduino).

---

## ✨ Features

- ✅ Temperature control using a sliding potentiometer (5°C – 18°C)
- 🌡️ Real-time evaporator temperature reading via NTC 10k
- 🧊 Clean evaporator coils
- 🔁 ECU integration with AC permission signal + manual bypass switch
- 🔧 Compatible with **Arduino Uno** and **Mega 2560**
- 💡 TM1637 7-segment display shows:
  - Setpoint (`XX°C`)
  - Actual evaporator temperature
  - Status words: `INIT`, `WAIT`, `COOL`
 
---

## 🛠️ Hardware Requirements

- Arduino Uno / Mega 2560
- TM1637 4-digit 7-segment display
- 10k NTC thermistor + 10k pull-down resistor
- Potentiometer analog (0–5V)
- Relay modules (compressor, blower cut, blower speed 4)
- PlatformIO (VS Code) or Arduino IDE

---

## 📐 Pin Mapping

| Component              | Uno Pin      | Mega2560 Pin |
|------------------------|--------------|--------------|
| TM1637 CLK / DIO       | 2 / 3        | 22 / 23      |
| Potentiometer          | A0           | A0           |
| NTC Thermistor         | A1           | A1           |
| Freeze Button          | 5            | 24           |
| Blower Cut Relay       | 7            | 26           |
| Blower Speed 4 Relay   | 6            | 25           |
| Compressor Relay       | 8            | 27           |
| AC Request (to ECU)    | 9            | 28           |
| ECU Permission (input) | 10           | 29           |
| Bypass Switch          | 11           | 30           |

---

## 📋 Display Output States
INIT → Initialization (2 seconds)

XX°C → Setpoint (for 3s after adjusting) or real-time temp

WAIT → Waiting for ECU permission

COOL → Cleaning process active

---

![License](https://img.shields.io/badge/license-MIT-green.svg) 

Made with 🍵 by GreenArtDe Project

Inspired by real-world automotive climate needs.
