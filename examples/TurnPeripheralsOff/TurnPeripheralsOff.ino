/**
 * This example builds on the Standby Example which puts the microcontroller of the Portenta H7 into
 * standby mode for 10 seconds by also turning off most of the peripherals on the board using the PF1550 PMIC.
 * This example turns off the following power rails on the PMIC:
 * * LDO1 - ANX7625 video bridge 
 * * LDO2 - onboard misc. chips
 * * LDO3 - 1.2V for Ethernet
 * * SW1 - Ethernet PHY, SDRAM, USB PHY
 * * SW2 - External Power Regulator
 * 
 * Original author: A. Vidstrom (http://arduino.cc)
 * Updated by: C. Dragomir (http://arduino.cc)
 * This code is in the public domain
 */

// WARNING: The following #define disables automatically turning off the Ethernet chip when the
//          microcontroller goes into Standby Mode. Doing so can damage the Ethernet transmission
//          termination resistors unless the power to the Ethernet chip is turned off manually,
//          as in this example sketch, before entering Standby Mode.
// -->
#define NO_ETHERNET_TURN_OFF
// <--

#include "Arduino_LowPowerPortentaH7.h"
#include "Arduino_PMIC.h"
#include "Wire.h"

void setup() {

  #if defined CORE_CM7
    if (LowPowerReturnCode::success != LowPower.checkOptionBytes()) {
        LowPower.prepareOptionBytes();
    }
    bootM4();
  #endif

  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDB, LOW);
  delay(1000);

  #if defined CORE_CM7
    PMIC.begin();

    // Turn off the ANX7625 video bridge
    PMIC.getControl() -> turnLDO1Off(Ldo1Mode::Normal);

    // Turn off misc onboard chips
    PMIC.getControl() -> turnLDO2Off(Ldo2Mode::Normal);

    // Turn off the 1.2V for Ethernet
    PMIC.getControl() -> turnLDO3Off(Ldo3Mode::Normal);

    // Turn off the Ethernet PHY, SDRAM, and USB PHY
    PMIC.getControl() -> turnSw1Off(Sw1Mode::Normal);

    // Turn off the external power regulator
    PMIC.getControl() -> turnSw2Off(Sw2Mode::Normal);

    // Turn off the I2C bus as the PMIC might try to communicate with the microcontroller
    Wire1.end();

    

    LowPower.standbyM7(LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed, 10 s);
    //
    // The following is an alternative way to go into Standby Mode for 10 seconds:
    // LowPower.standbyM7(LowPowerStandbyType::untilTimeElapsed, RTCWakeupDelay(0, 0, 10));
    //
    // The following is how to go to into Standby Mode waiting only for a wakeup pin:
    // LowPower.standbyM7(LowPowerStandbyType::untilPinActivity);
    //
  #else
    LowPower.standbyM4();
  #endif
}

void loop() {}
