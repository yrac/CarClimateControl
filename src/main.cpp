#include <Arduino.h>
#include "ACController.h"

ACController ac;

void setup() {
    ac.begin();
}

void loop() {
    ac.loop();
    delay(10); // Hindari CPU 100%, cukup ringan
}