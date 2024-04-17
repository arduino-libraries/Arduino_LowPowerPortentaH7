/**
* This example shows how to get the microcontroller of the Portenta H7 into
* standby mode for 10 seconds. Stand by mode consumes the least amount of power.
* However you will loose the Serial connection and the USB connection.
* Therefore we use the LEDs to signal the different states.
* 
* The microcontroller has three power domains: one for the M7 core (D1), 
* one for the M4 core (D2), and a separate third domain (D3) for some other functionality.
* When all three domains are in standby mode simultaneously, the microcontroller as a whole 
* enters Standby Mode automatically, and `modeWasStandby()` only returns true when it wakes up again.
*
* IMPORTANT: Upload the same sketch to both the M7 and the M4 core.
*
* The LED light should follow this sequence:
*
*   - Cyan   = Both cores are running
*   - Yellow = The last state will follow
*   - Green  = The microcontroller was in standby mode (not the first time)
*   - Yellow = The last state was just reported
*   - White  = Standby Mode will be entered soon
*
* This sequence repeats indefinitely.
*
* Original author: A. Vidstrom (http://arduino.cc)
*
* This code is in the public domain
*/

#include "Arduino_LowPowerPortentaH7.h"

void setup() {

#if defined CORE_CM7
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  if (LowPowerReturnCode::success != LowPower.checkOptionBytes())
  {
    LowPower.prepareOptionBytes();
  }
  bootM4();
#endif

  // Blue when M7 is starting and green when M4 is starting, which
  // gives cyan when both are starting at the same time
#if defined CORE_CM7
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDR, HIGH);
#else
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
#endif
  delay(2500);

  // Go silent for a second to separate the next step
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);
  delay(1000);

  // Signal the previous standby mode with colors
  //
  // First, a yellow blink, then, any combination of these
  // in the following order:
  //
  // Green  = The whole microcontroller was in standby mode
  // Blue   = Domain 1 was in standby mode
  // Red    = Domain 2 was in standby mode
  // Purple = The whole microcontroller was in stop mode
  //
  // Last, a yellow blink
  // -->
#if defined CORE_CM7
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  delay(500);
  if (LowPower.modeWasStandby())
  {
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    delay(2500);
  }
  if (LowPower.modeWasD1Standby())
  {
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    delay(2500);      
  }
  if (LowPower.modeWasD2Standby())
  {
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    delay(2500);      
  }
  if (LowPower.modeWasStop())
  {
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    delay(2500);      
  }
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  delay(500);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  delay(500);
  LowPower.resetPreviousMode();
#endif
  // <--

  // White to signal that sleep will happen soon
#if defined CORE_CM7
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDR, LOW);
  delay(2500);
#endif

#if defined CORE_CM7
  LowPower.standbyM7(LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed, 10_s);
  // The following is an alternative way to go into standby for 10 seconds
  // LowPower.standbyM7(LowPowerStandbyType::untilTimeElapsed, RTCWakeupDelay(0, 0, 10));
#else
  LowPower.standbyM4();
#endif
}

void loop() {}
