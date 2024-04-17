/*
********************************************************************************
*
* This example shows how to allow Deep Sleep on the Portenta H7 using the Mbed OS based core.
* Deep Sleep Mode is a deeper kind of sleep that saves more power, but it's blocked 
* by something called Deep Sleep Locks. They can be released by calling the 
* LowPower.allowDeepSleep() function.
*
* The blue LED turns on first, for 5 seconds. The delay is performed with a call
* to delay(), which will trigger Sleep Mode automatically. Then, the red LED is
* turned on for an amount of time that equals the time spent in Sleep Mode. The
* expected behavior is that these two delays should be roughly equal.
*
* Next, the sketch makes a call to allow Deep Sleep Mode. It then turns the blue
* LED on for 5 seconds again, using a delay() call exactly as last time. Next,
* the green LED is turned on for an amount of time that equals the time spent in
* Deep Sleep Mode. The expected behavior is that these two delays should be
* roughly equal.
*
* Original author: A. Vidstrom (http://arduino.cc)
*
* This code is in the public domain
*
*/

#include "Arduino_LowPowerPortentaH7.h"

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);

  // Turn on the blue LED and call delay(5000) to
  // trigger some automatic Sleep
  digitalWrite(LEDB, LOW);
  delay(5000);
  digitalWrite(LEDB, HIGH);
  
  // Turn on the red LED instead, for an equal amount
  // of time as was spent in Sleep
  digitalWrite(LEDR, LOW);
  delayMicroseconds(LowPower.timeSpentInSleep());
  digitalWrite(LEDR, HIGH);

  // Now allow Deep Sleep
  LowPower.allowDeepSleep();
  // Turn on the blue LED and call delay(5000) to
  // trigger some automatic Deep Sleep
  digitalWrite(LEDB, LOW);
  delay(5000);
  digitalWrite(LEDB, HIGH);
  
  // Turn on the green LED instead, for an equal amount
  // of time as was spent in Deep Sleep
  digitalWrite(LEDG, LOW);
  delayMicroseconds(LowPower.timeSpentInDeepSleep());
  digitalWrite(LEDG, HIGH);
}

void loop() {
}
