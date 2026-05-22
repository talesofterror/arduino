#include <Arduino.h>

void setup()
{
  // 1. Initialize the USB Serial port (for debugging on your computer)
  Serial.begin(9600);

  // 2. Initialize the hardware UART port (Pins 0 and 1)
  // Teensy ignores the baud rate for USB Serial, but hardware UART requires it.
  // Common baud rates: 9600, 115200, 31250 (for MIDI)
  Serial1.begin(115200);

  // Wait a moment for USB serial connection to stabilize
  while (!Serial && millis() < 2000);
  Serial.println("Teensy 4.1 UART Initialized.");
}

int iterationNumber = 0;

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  // Sending data out of Teensy Pin 1 (TX1)
  Serial1.println("Hello from Teensy!");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  // Receiving data coming into Teensy Pin 0 (RX1)
  if (Serial1.available() > 0) {

    Serial.print(iterationNumber++);
    Serial.print(" // ");
    Serial.print("Received hardware data: \n");

    while (Serial1.available() > 0)
    {
  
      // Read the incoming byte
      char incomingByte = Serial1.read();
  
      // Echo it back to your computer's serial monitor so you can see it
      Serial.print(incomingByte);
    }
  }

  delay(200);
}
