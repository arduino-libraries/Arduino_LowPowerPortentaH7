/**
* This example shows how to debug Deep Sleep Locks on the Portenta H7.
* Deep Sleep Locks are used by Mbed OS to prevent the microcontroller from entering Deep Sleep.
*
* The sketch prints a line that tells if Deep Sleep Mode is possible or not. It
* also prints a line with the number of currently active Deep Sleep Locks. This
* number should (in this default case) be either 2 or 3 unless you call allowDeepSleep() . 
* Which of these is printed can vary from run to run. 
*
* You can use this sketch to debug your own
* code and see if you have any Deep Sleep Locks that could not be released.
* In this case canDeepSleep() would return false.
*
* Original author: A. Vidstrom (http://arduino.cc)
*
* This code is in the public domain
*/

#include "Arduino_LowPowerPortentaH7.h"

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.print("Deep Sleep is possible: ");
  LowPower.canDeepSleep() ? Serial.println("Yes") : Serial.println("No");
  // The expected number here is 2 or 3 (can vary from run to run)
  Serial.print("Number of Deep Sleep Locks currently active: ");
  Serial.println(LowPower.numberOfDeepSleepLocks());
}

void loop() {
}
