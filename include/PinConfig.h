#pragma once

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_PRO)
  #define POT_PIN            A0
  #define NTC_PIN            A1
  #define TM1637_CLK_PIN     2
  #define TM1637_DIO_PIN     3
  #define FREEZE_BTN_PIN     4
  #define RELAY_BLOWER_CUT   5
  #define RELAY_BLOWER_4     6
  #define RELAY_COMPRESSOR   7
  #define ECU_REQUEST_OUT    8
  #define ECU_PERMISSION_IN  9
  #define BYPASS_SWITCH_PIN  10

#elif defined(ARDUINO_AVR_MEGA2560)
  #define POT_PIN            A0
  #define NTC_PIN            A1
  #define TM1637_CLK_PIN     22
  #define TM1637_DIO_PIN     26
  #define FREEZE_BTN_PIN     24
  #define RELAY_BLOWER_4     25
  #define RELAY_BLOWER_CUT   26
  #define RELAY_COMPRESSOR   27
  #define ECU_REQUEST_OUT    28
  #define ECU_PERMISSION_IN  29
  #define BYPASS_SWITCH_PIN  30

#else
  #error "Unsupported board! Please define pin configuration."
#endif