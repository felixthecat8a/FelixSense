#include <FelixSense.h>

const unsigned long timeInterval = 1000;
unsigned long startTime = 0;

bool done = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  AsyncTime::reset(startTime); // arm
}

void loop() {
  if (AsyncTime::once(3000, startTime)) {
    Serial.println("3 seconds passed!");
  }

  /* similar behavior */

  // if (AsyncTime::after(3000, startTime && !done)) {
  //   done = true;
  //   Serial.println("3 seconds passed!");
  // }
}
