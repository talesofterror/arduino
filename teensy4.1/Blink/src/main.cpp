#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
  delay(200);
}
