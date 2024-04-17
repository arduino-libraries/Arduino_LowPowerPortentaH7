# ⚡️ Arduino Portenta H7 Low Power Library
[![Arduino Lint](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/arduino-lint.yml) [![Compile Examples](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/spell-check.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/sync-labels.yml) [![Render Documentation](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/render-documentation.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_LowPowerPortentaH7/actions/workflows/render-documentation.yml)
[![License](https://img.shields.io/badge/License-MPL_2.0-blue)](http://mozilla.org/MPL/2.0/)

The Arduino Portenta H7 Low Power library provides functionality to enable, get information about, and debug low-power modes on the Portenta H7 board.

## ✨ Features

- Functionality related to Deep Sleep
- Functionality related to Standby Mode

## 📖 Documentation

For more information about this library please read the documentation [here](./docs).

## 💡 Technical Background

There are three different low-power modes available:

- Sleep Mode
- Deep Sleep Mode
- Standby Mode

### 😪 Sleep Mode

Sleep Mode is entered automatically in certain situations when you use the standard Arduino Mbed Core, for example, when you call `delay()`. But it's also the mode that saves the least power, which is why this library exists. 

### 🥱 Deep Sleep Mode

Deep Sleep Mode is a deeper kind of sleep that saves more power, but it's blocked by something called Deep Sleep Locks. By default, two or three such locks are held at all times. One of them is periodically acquired and then quickly released again. The other two are held continuously but can be released by calling the `LowPower.allowDeepSleep()` function. When no Deep Sleep Locks are held anymore, Mbed automatically replaces Sleep Mode with Deep Sleep Mode. This saves more power and is the best option if your application is meant to run all the time but you still wish to save as much power as possible.

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

### 😴 Standby Mode

In Standby Mode, both the sketch and Mbed are entirely stopped by the library, and it asks the microcontroller to turn off almost all functionality to save power. You can wake it up from this mode in two ways: pulling the GPIO 0 pin low on the Portenta Breakout Board (no external pull-up resistor is necessary) or asking the library to wake up after a certain amount of time. The delay can be set anywhere from 1 second up to 36 hours, 24 minutes, and 32 seconds. When the board wakes up again, it's more or less in the same state as it would have been if you had pressed the reset button. You can ask the library what the board was doing before it started by calling one or a combination of the functions: `modeWasD1Standby()`, `modeWasD2Standby()`, `modeWasStandby()`, and `modeWasStop()`.

## ⚖️ License

This library is released under the [MPL-2.0 license](http://mozilla.org/MPL/2.0/).
