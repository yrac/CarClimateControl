#include "DisplayManager.h"
#include "ACController.h"

DisplayManager display;
ACController acController(display);

void setup() {
  acController.begin();
}

void loop() {
  acController.update();
}