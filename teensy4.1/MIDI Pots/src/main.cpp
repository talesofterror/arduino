#include <Arduino.h>

void blinker();

const int potPin = 14;  // Middle pin of pot connected to A0/Pin 14
int lastMidiValue = -1; // Tracks the previous value to prevent spamming duplicate messages

elapsedMillis timeSinceLastRead;
const int checkInterval = 20; // Check the pot every 20ms for smooth tracking

// Choose a MIDI CC number (CC 7 is standard for Volume, CC 74 for Filter Cutoff)
const int ccNumber = 74;
const int midiChannel = 1; // MIDI channel 1

elapsedMillis timeSinceLEDWrite;
boolean ledOn = false;

void setup()
{
  pinMode(potPin, INPUT);
}

void loop()
{
  if (timeSinceLastRead >= checkInterval)
  {
    int rawValue = analogRead(potPin);

    // Scale the raw 10-bit value (0-1023) down to a 7-bit MIDI value (0-127)
    int currentMidiValue = map(rawValue, 0, 1023, 0, 127);

    // Only send a message if the knob actually moved.
    // This stops identical messages.
    if (currentMidiValue != lastMidiValue)
    {

      // Send the Control Change message: (CC Number, Value, Channel)
      usbMIDI.sendControlChange(ccNumber, currentMidiValue, midiChannel);

      // Update our tracker
      lastMidiValue = currentMidiValue;
    }

    // Only update if the knob moves by more than 1 unit on the scale,
    // or if it successfully reaches the absolute maximum/minimum boundaries.
    if (abs(currentMidiValue - lastMidiValue) > 1 ||
        (currentMidiValue == 0 && lastMidiValue != 0) ||
        (currentMidiValue == 127 && lastMidiValue != 127))
    {

      usbMIDI.sendControlChange(ccNumber, currentMidiValue, midiChannel);
      lastMidiValue = currentMidiValue;
    }

    timeSinceLastRead = 0;
  }
  
  blinker();
  // MIDI Controllers should read incoming messages quickly to stay compliant
  while (usbMIDI.read())
  {
    // We aren't receiving incoming MIDI sync/data right now, but we clear the buffer anyway
  }
}

void blinker()
{
  int rawValue = analogRead(potPin);
  int blinkInterval = map(rawValue, 0, 1023, 1000, 50);

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