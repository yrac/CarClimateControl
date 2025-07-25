#include <Arduino.h>
#include "ACController.h"

ACController ac;

void setup() {
  ac.begin();
}

void loop() {
  ac.update();
}