#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#ifdef ARDUINO_AVR_MEGA2560

  // === RELAY OUTPUTS (MEGA) ===
  #define PIN_COMPRESSOR_RELAY   22  // Controls the compressor relay (LOW = ON)
  #define PIN_BLOWER_RELAY       26  // Controls main blower relay

  // === BLOWER SPEED RELAY PINS (WERSTAN-style) ===
  #define PIN_BLOWER_SPEED1      30  // Speed 1 (lowest)
  #define PIN_BLOWER_SPEED2      34
  #define PIN_BLOWER_SPEED3      38
  #define PIN_BLOWER_SPEED4      42  // Speed 4 (highest)

  // === INPUTS ===
  #define PIN_FREEZE_BUTTON      46  // Multi-function button (freeze, menu)
  #define PIN_SPEEDUINO_IN       48  // From ECU: LOW = permission granted to activate compressor

  // === OUTPUTS ===
  #define PIN_SPEEDUINO_OUT      44  // To ECU: LOW = request permission to activate compressor
  #define PIN_BUZZER             50  // Active buzzer pin

  // === DISPLAY (TM1637 4-digit) ===
  #define PIN_TM1637_CLK         52  // TM1637 clock pin
  #define PIN_TM1637_DIO         53  // TM1637 data pin

#else
  // === RELAY OUTPUTS (UNO) ===
  #define PIN_COMPRESSOR_RELAY    2
  #define PIN_BLOWER_RELAY        3

  // === BLOWER SPEED RELAY PINS (UNO) ===
  #define PIN_BLOWER_SPEED1       4
  #define PIN_BLOWER_SPEED2       5
  #define PIN_BLOWER_SPEED3       6
  #define PIN_BLOWER_SPEED4       7

  // === INPUTS (UNO) ===
  #define PIN_FREEZE_BUTTON       8
  #define PIN_SPEEDUINO_IN        9

  // === OUTPUTS (UNO) ===
  #define PIN_SPEEDUINO_OUT      10
  #define PIN_BUZZER             11
  #define PIN_TM1637_CLK         12
  #define PIN_TM1637_DIO         13

#endif

// === ANALOG INPUTS (common for all boards) ===
#define PIN_NTC_SENSOR         A0   // NTC 10k temperature sensor (evaporator)
#define PIN_POTENTIOMETER      A1   // Slider potentiometer for target temperature

#endif // PIN_CONFIG_H