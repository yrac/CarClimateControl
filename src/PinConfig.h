#pragma once

#if defined(ARDUINO_AVR_UNO)
  #define POT_PIN           A0
  #define NTC_PIN           A1
  #define TM1637_CLK_PIN    2
  #define TM1637_DIO_PIN    3
  #define FREEZE_BTN_PIN    5
  #define BLOWER_SPEED4_PIN 6
  #define BLOWER_CUT_PIN    7
  #define RELAY_AC_PIN      8
  #define AC_REQUEST_PIN    9
  #define AC_PERMISSION_PIN 10
  #define BYPASS_SWITCH_PIN 11
#elif defined(ARDUINO_AVR_MEGA2560)
  #define POT_PIN           A0
  #define NTC_PIN           A1
  #define TM1637_CLK_PIN    22
  #define TM1637_DIO_PIN    23
  #define FREEZE_BTN_PIN    24
  #define BLOWER_SPEED4_PIN 25
  #define BLOWER_CUT_PIN    26
  #define RELAY_AC_PIN      27
  #define AC_REQUEST_PIN    28
  #define AC_PERMISSION_PIN 29
  #define BYPASS_SWITCH_PIN 30
#else
  #error "Unsupported board! Please define pin configuration."
#endif