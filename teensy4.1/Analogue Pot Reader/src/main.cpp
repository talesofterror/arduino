#include <Arduino.h>

// Define the analog pin you connected the middle wiper pin to
const int potPin = 14; // Pin 14 is also Analog Pin A0

// Special Teensy timer variables that increment automatically in the background
elapsedMillis timeSinceAnalogueRead;
elapsedMillis timeSinceLEDWrite;
boolean ledOn = false;

void setup()
{
  // Initialize USB serial communication for your computer
  Serial.begin(9600);

  // Wait a moment for the serial monitor to connect
  while (!Serial && millis() < 2000)
    ;

  Serial.println("Potentiometer Test Initialized.");
}


void loop()
{
  // Read the raw analog voltage value (returns a number from 0 to 1023)
  int potValue = analogRead(potPin);

  // Convert the 0-1023 value into a voltage string just for display
  float voltage = potValue * (3.3 / 1023.0);

  if (timeSinceAnalogueRead > 150)
  {

    // Print the raw value and the calculated voltage to the Serial Monitor
    Serial.print("Raw Value: ");
    Serial.print(potValue);
    Serial.print("  |  Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    // A small delay to keep the Serial Monitor readable
    // delay(100);

    timeSinceAnalogueRead = 0;
  }

  // blink the LED at a rate dependant on voltage
  // if (timeSinceLEDWrite > 500 / (voltage + 0.01))
  // {
  //   if (ledOn)
  //   {
  //     digitalWrite(LED_BUILTIN, HIGH);
  //     ledOn = false;
  //   }
  //   else
  //   {
  //     digitalWrite(LED_BUILTIN, LOW);
  //     ledOn = true;
  //   }
  //   timeSinceLEDWrite = 0;
  // }

  // Map raw pot values (0 to 1023) directly to blink intervals (2000ms down to 50ms)
  // similar to above but using Arduino's map() function
  int blinkInterval = map(potValue, 0, 1023, 1000, 50);

  if (timeSinceLEDWrite > blinkInterval)
  {
    if (ledOn)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      ledOn = false;
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
      ledOn = true;
    }
    timeSinceLEDWrite = 0;
  }
}