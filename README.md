# ⚡️ Arduino Portenta H7 Low Power Libray
[![Arduino Lint](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/arduino-lint.yml) [![Compile Examples](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/spell-check.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/sync-labels.yml) [![Render Documentation](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/render-documentation.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/render-documentation.yml)
[![License](https://img.shields.io/badge/License-MPL_2.0-blue)](http://mozilla.org/MPL/2.0/)

The Arduino Portenta H7 Low Power library provides functionality to enable, get information about, and debug low-power modes on the Portenta H7 board.

## ✨ Features

- Functionality related to Deep Sleep
- Functionality related to Standby Mode

## Technical Background

There are three different low-power modes available:

- Sleep Mode
- Deep Sleep Mode
- Standby Mode

### Sleep Mode

Sleep Mode is entered automatically in certain situations when you use the standard Arduino Mbed Core, for example, when you call delay(). But it's also the mode that saves the least power, which is why this library exists. 

### Deep Sleep Mode

Deep Sleep Mode is a deeper kind of sleep that saves more power, but it's blocked by something called Deep Sleep Locks. By default, two or three such locks are held at all times. One of them is periodically acquired and then quickly released again. The other two are held continuously but can be released by calling the LowPower.allowDeepSleep() function. When no Deep Sleep Locks are held anymore, Mbed automatically replaces Sleep Mode with Deep Sleep Mode. This saves more power and is the best option if your application is meant to run all the time but you still wish to save as much power as possible.

In addition to the three Deep Sleep Locks already mentioned, additional locks may be held depending on the functionality you use:

- During I2C transfers
- While some timers are running
- Continuously when you use Ethernet
- During SPI transfers
- Continuously when you use PWM
- When a callback is attached for CAN receives
- Continuously when WiFi is used
- Continuously when BLE is used (more than one lock may be held in this case)
- At certain times, when using various serial connections

### Standby Mode

In Standby Mode, both the sketch and Mbed are entirely stopped by the library, and it asks the microcontroller to turn off almost all functionality to save power. You can wake it up from this mode in two ways: pulling the GPIO 0 pin low on the Portenta Breakout Board (no external pull-up resistor is necessary) or asking the library to wake up after a certain amount of time. The delay can be set anywhere from 1 second up to 36 hours, 24 minutes, and 32 seconds. When the board wakes up again, it's more or less in the same state as it would have been if you had pressed the reset button. You can ask the library what the board was doing before it started by calling one or a combination of the functions: modeWasD1Standby(), modeWasD2Standby(), modeWasStandby(), and modeWasStop().

## 👀 Usage

Start by including the library header file:

```cpp
#include "Arduino_LowPowerPortentaH7.h"
```

What you do next depends on what you want to achieve. Using only one of Deep Sleep Mode and Standby Mode might be sufficient, or you might want to combine them. If you combine them, start by enabling Deep Sleep Mode, perform any necessary work, and let the board go into Standby Mode until you need to perform more work.

### Deep Sleep Mode

The only function necessary to enable automatic Deep Sleep Mode is allowDeepSleep(). You might also find the following functions helpful: canDeepSleep(), timeSinceBoot(), timeSpentIdle(), timeSpentInSleep(), and timeSpentInDeepSleep(). Another function that can be useful when debugging Deep Sleep Locks, but not for production code, is numberOfDeepSleepLocks().

> [!CAUTION]
> The numberOfDeepSleepLocks() function should never be used in production code because it relies on undocumented functionality in Mbed.

### Standby Mode

To use Standby Mode, you need the following functions: checkOptionBytes(), prepareOptionBytes(), standbyM7(), and standbyM4(). The option byte functions are necessary to ensure that the flash option bytes in the microcontroller are correctly set for going into Standby Mode. Additionally, you can use the following functions to check what the board was doing before it started: modeWasD1Standby(), modeWasD2Standby(), modeWasStandby(), and modeWasStop(). Only modeWasStandby() should return true if Standby Mode was entered correctly. The other functions can be handy for troubleshooting. Remember to clear the mode flags by calling resetPreviousMode() when you are done checking them.

The microcontroller has three power domains: one for the M7 core (D1), one for the M4 core (D2), and a separate third domain (D3) for some other functionality. modeWasD1Standby() returns true if D1 was in standby, but all three weren't at the same time, while modeWasD2Standby() returns true if D2 was in standby, but all three weren't at the same time. Both functions can return true simultaneously if D1 and D2 were in standby mode while D3 was still awake. When all three domains are in standby mode simultaneously, the microcontroller as a whole enters Standby Mode automatically, and only modeWasStandby() returns true when it wakes up again. The modeWasStop() function should never return true but can be helpful for further troubleshooting if you contact Arduino support.

All configuration of Standby Mode is done when calling standbyM7(). It takes one or two parameters, depending on the conditions you want to set for waking up. The first parameter is one of the flags LowPowerStandbyType::untilPinActivity and LowPowerStandbyType::untilTimeElapsed. If you want to wake up from either type of event, you can combine the flags like so: LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed. If LowPowerStandbyType::untilTimeElapsed is present, the function takes a second parameter. This parameter's preferred format is 2_h + 30_min + 45_s. You can use any combination of hours, minutes, and seconds. For example, 15_h, or 1_h + 30_min, or just 90_s. If you first have to calculate the delay in your sketch, you can also pass something like this: RTCWakeupDelay(1, 20, 30). The first number is hours, the second minutes, and the third seconds. But, the preferred option is to use _h, _min, and _s since that's more explicit.

> [!NOTE]
> You must always upload a sketch to the M4 core, in which you call standbyM4(), even if you don't intend to use the M4 core. If you don't, the microcontroller won't enter Standby Mode as a whole, even if you call standbyM7().

## Examples

- **Standby_Example:** This example demonstrates how to enter Standby Mode for a few seconds and then wake up again. It's also possible to wake up early by pulling the GPIO 0 pin low on the Portenta Breakout Board.
- **AllowDeepSleep_Example:** This example demonstrates how to enable Deep Sleep Mode.
- **DeepSleepLockDebug_Example:** This example demonstrates how to debug Deep Sleep Lock problems.

## 📖 Documentation

For more information about this library please read the documentation [here](./docs).

## License

This library is released under the [MPL-2.0 license](http://mozilla.org/MPL/2.0/).
