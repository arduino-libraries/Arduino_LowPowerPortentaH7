# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`LowPowerPortentaH7`](#class_low_power_portenta_h7) | A class that provides low power functionality for the Portenta H7 board.
`class ` [`LowPowerStandbyType`](#class_low_power_standby_type) | The [LowPowerStandbyType](#class_low_power_standby_type) class represents different types of standby modes for low power operation.
`class ` [`RTCWakeupDelay`](#class_r_t_c_wakeup_delay) | The [RTCWakeupDelay](#class_r_t_c_wakeup_delay) class represents a delay before waking up from a low power mode.
`class ` [`LowPowerStandbyType::UntilEitherClass`](#class_low_power_standby_type_1_1_until_either_class) | Represents a wakeup option which waits until either a pin activity occurs or a specified time has elapsed.
`class ` [`LowPowerStandbyType::UntilPinActivityClass`](#class_low_power_standby_type_1_1_until_pin_activity_class) | Class representing an activity that waits until a pin changes its state.
`class ` [`LowPowerStandbyType::UntilTimeElapsedClass`](#class_low_power_standby_type_1_1_until_time_elapsed_class) | A class representing a time elapsed condition.

# class `LowPowerPortentaH7` <a id="class_low_power_portenta_h7" class="anchor"></a>

A class that provides low power functionality for the Portenta H7 board.

The [LowPowerPortentaH7](#class_low_power_portenta_h7) class allows the microcontroller on the Portenta H7 board to enter low power modes such as Standby Mode and Deep Sleep Mode. It provides functions to check the current mode, prepare the option bytes for entering Standby Mode, and control the M4 and M7 cores independently. It also provides functions to measure the time since boot, time spent in idle, sleep, and deep sleep modes.

This class is a singleton and can be accessed using the [getInstance()](#class_low_power_portenta_h7_1aa852067ffc101c0cb7ac526cc91080b4) function.

This class is specific to the Portenta H7 board.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`allowDeepSleep`](#class_low_power_portenta_h7_1a7ed518f8205a0b7306d23b7e2a22e82b) | Make Deep Sleep possible in the default case. |
| [`canDeepSleep`](#class_low_power_portenta_h7_1a07d9e0f356e40ac70655e279fbad87a9) | Check if Deep Sleep is possible or not at the moment. |
| [`checkOptionBytes`](#class_low_power_portenta_h7_1a7519d3acf693f450af84312576d8e669) | Check if the option bytes are correct to enter Standby Mode. |
| [`modeWasD1Standby`](#class_low_power_portenta_h7_1a4eb99fd03e8891f93d43aca4ea2329f9) | Check if the D1 domain was in Standby Mode or not. |
| [`modeWasD2Standby`](#class_low_power_portenta_h7_1a81e1c97f6411de6c6df390f7cb1ef8dc) | Check if the D2 domain was in Standby Mode or not. |
| [`modeWasStandby`](#class_low_power_portenta_h7_1afb2fc28d8a59bc34799e4c83a746f7c4) | Check if the whole microcontroller was in Standby Mode or not. |
| [`modeWasStop`](#class_low_power_portenta_h7_1a8420caa1148e61bc4d40e9627866afe3) | Check if the whole microcontroller was in Stop Mode or not. |
| [`numberOfDeepSleepLocks`](#class_low_power_portenta_h7_1a9d2730d86abf42782261b0f03778c3bb) | Check how many Deep Sleep locks are held at the moment. |
| [`prepareOptionBytes`](#class_low_power_portenta_h7_1abdc0ce13b68d3a2188702690997af2ae) | Prepare the option bytes for entry into Standby Mode. |
| [`resetPreviousMode`](#class_low_power_portenta_h7_1a6f09b3ffe26355372f287ab90a451cc2) | Reset the flags behind the modeWas...() functions. |
| [`standbyM4`](#class_low_power_portenta_h7_1a9e07fd4f7895a7753e7e28f99aca1ace) | Make the M4 core enter Standby Mode. |
| [`standbyM7`](#class_low_power_portenta_h7_1a1eb5cec6e9604a48074f1c10ef5e7fb0) | Make the M7 core enter Standby Mode. |
| [`timeSinceBoot`](#class_low_power_portenta_h7_1a4758c25574b6d099545ac8d55eff6f68) | Time since the board was booted. |
| [`timeSpentIdle`](#class_low_power_portenta_h7_1ad42fdfa6885d8e0fdca5aa012fdb4c60) | Time spent in idle. |
| [`timeSpentInSleep`](#class_low_power_portenta_h7_1a994eb6fcc0382515a82b81fa37ca9f3c) | Time spent in Sleep Mode. |
| [`timeSpentInDeepSleep`](#class_low_power_portenta_h7_1a146eb61800a74360687fd34b456c0b44) | Time spent in Deep Sleep Mode. |
| [`getInstance`](#class_low_power_portenta_h7_1aa852067ffc101c0cb7ac526cc91080b4) | Returns the singleton instance of the [LowPowerPortentaH7](#class_low_power_portenta_h7) class. Due to the way the low power modes are configured, only one instance of this class can exist at a time. |

## Members

### `allowDeepSleep` <a id="class_low_power_portenta_h7_1a7ed518f8205a0b7306d23b7e2a22e82b" class="anchor"></a>

```cpp
void allowDeepSleep() const
```

Make Deep Sleep possible in the default case.

<hr />

### `canDeepSleep` <a id="class_low_power_portenta_h7_1a07d9e0f356e40ac70655e279fbad87a9" class="anchor"></a>

```cpp
bool canDeepSleep() const
```

Check if Deep Sleep is possible or not at the moment.

#### Returns
Possible: true. Not possible: false.
<hr />

### `checkOptionBytes` <a id="class_low_power_portenta_h7_1a7519d3acf693f450af84312576d8e669" class="anchor"></a>

```cpp
LowPowerReturnCode checkOptionBytes() const
```

Check if the option bytes are correct to enter Standby Mode.

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `modeWasD1Standby` <a id="class_low_power_portenta_h7_1a4eb99fd03e8891f93d43aca4ea2329f9" class="anchor"></a>

```cpp
bool modeWasD1Standby() const
```

Check if the D1 domain was in Standby Mode or not.

#### Returns
Was: true. Was not: false;
<hr />

### `modeWasD2Standby` <a id="class_low_power_portenta_h7_1a81e1c97f6411de6c6df390f7cb1ef8dc" class="anchor"></a>

```cpp
bool modeWasD2Standby() const
```

Check if the D2 domain was in Standby Mode or not.

#### Returns
Was: true. Was not: false;
<hr />

### `modeWasStandby` <a id="class_low_power_portenta_h7_1afb2fc28d8a59bc34799e4c83a746f7c4" class="anchor"></a>

```cpp
bool modeWasStandby() const
```

Check if the whole microcontroller was in Standby Mode or not.

#### Returns
Was: true. Was not: false;
<hr />

### `modeWasStop` <a id="class_low_power_portenta_h7_1a8420caa1148e61bc4d40e9627866afe3" class="anchor"></a>

```cpp
bool modeWasStop() const
```

Check if the whole microcontroller was in Stop Mode or not.

#### Returns
Was: true. Was not: false;
<hr />

### `numberOfDeepSleepLocks` <a id="class_low_power_portenta_h7_1a9d2730d86abf42782261b0f03778c3bb" class="anchor"></a>

```cpp
uint16_t numberOfDeepSleepLocks() const
```

Check how many Deep Sleep locks are held at the moment.

#### Returns
The number held.
<hr />

### `prepareOptionBytes` <a id="class_low_power_portenta_h7_1abdc0ce13b68d3a2188702690997af2ae" class="anchor"></a>

```cpp
LowPowerReturnCode prepareOptionBytes() const
```

Prepare the option bytes for entry into Standby Mode.

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `resetPreviousMode` <a id="class_low_power_portenta_h7_1a6f09b3ffe26355372f287ab90a451cc2" class="anchor"></a>

```cpp
void resetPreviousMode() const
```

Reset the flags behind the modeWas...() functions.

<hr />

### `standbyM4` <a id="class_low_power_portenta_h7_1a9e07fd4f7895a7753e7e28f99aca1ace" class="anchor"></a>

```cpp
LowPowerReturnCode standbyM4() const
```

Make the M4 core enter Standby Mode.

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `standbyM7` <a id="class_low_power_portenta_h7_1a1eb5cec6e9604a48074f1c10ef5e7fb0" class="anchor"></a>

```cpp
template<> std::enable_if< ArgumentsAreCorrect< T, Args... >::value, LowPowerReturnCode >::type standbyM7(const T standbyType, const Args... args) const
```

Make the M7 core enter Standby Mode.

#### Parameters
* `standbyType` One or a combination of [LowPowerStandbyType::untilPinActivity](#class_low_power_standby_type_1a75b13fb677c84d7c230d0a1e54a08344) and [LowPowerStandbyType::untilTimeElapsed](#class_low_power_standby_type_1ab25b40879f8cc709b48b40a70e4801d1). 

* `args` The delay before waking up again 

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `timeSinceBoot` <a id="class_low_power_portenta_h7_1a4758c25574b6d099545ac8d55eff6f68" class="anchor"></a>

```cpp
uint64_t timeSinceBoot() const
```

Time since the board was booted.

#### Returns
Number of microseconds.
<hr />

### `timeSpentIdle` <a id="class_low_power_portenta_h7_1ad42fdfa6885d8e0fdca5aa012fdb4c60" class="anchor"></a>

```cpp
uint64_t timeSpentIdle() const
```

Time spent in idle.

#### Returns
Number of microseconds.
<hr />

### `timeSpentInSleep` <a id="class_low_power_portenta_h7_1a994eb6fcc0382515a82b81fa37ca9f3c" class="anchor"></a>

```cpp
uint64_t timeSpentInSleep() const
```

Time spent in Sleep Mode.

#### Returns
Number of microseconds.
<hr />

### `timeSpentInDeepSleep` <a id="class_low_power_portenta_h7_1a146eb61800a74360687fd34b456c0b44" class="anchor"></a>

```cpp
uint64_t timeSpentInDeepSleep() const
```

Time spent in Deep Sleep Mode.

#### Returns
Number of microseconds.
<hr />

### `getInstance` <a id="class_low_power_portenta_h7_1aa852067ffc101c0cb7ac526cc91080b4" class="anchor"></a>

```cpp
inline static LowPowerPortentaH7 & getInstance() noexcept
```

Returns the singleton instance of the [LowPowerPortentaH7](#class_low_power_portenta_h7) class. Due to the way the low power modes are configured, only one instance of this class can exist at a time.

#### Returns
The singleton instance of the [LowPowerPortentaH7](#class_low_power_portenta_h7) class.
<hr />

# class `LowPowerStandbyType` <a id="class_low_power_standby_type" class="anchor"></a>

The [LowPowerStandbyType](#class_low_power_standby_type) class represents different types of standby modes for low power operation.

This class provides options for standby modes: waiting until pin activity or until a specified time has elapsed. It also allows to combine the two options.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `RTCWakeupDelay` <a id="class_r_t_c_wakeup_delay" class="anchor"></a>

The [RTCWakeupDelay](#class_r_t_c_wakeup_delay) class represents a delay before waking up from a low power mode.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`RTCWakeupDelay`](#class_r_t_c_wakeup_delay_1a63465af8bb8e25aecbe1d733527d588e) | Create a delay object for the RTC wakeup. |

## Members

### `RTCWakeupDelay` <a id="class_r_t_c_wakeup_delay_1a63465af8bb8e25aecbe1d733527d588e" class="anchor"></a>

```cpp
inline RTCWakeupDelay(const unsigned long long int hours, const unsigned long long int minutes, const unsigned long long int seconds)
```

Create a delay object for the RTC wakeup.

#### Parameters
* `hours` Hours to wait before wakeup. 

* `minutes` Minutes to wait before wakeup. 

* `seconds` Seconds to wait before wakeup.
<hr />

# class `LowPowerStandbyType::UntilEitherClass` <a id="class_low_power_standby_type_1_1_until_either_class" class="anchor"></a>

Represents a wakeup option which waits until either a pin activity occurs or a specified time has elapsed.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `LowPowerStandbyType::UntilPinActivityClass` <a id="class_low_power_standby_type_1_1_until_pin_activity_class" class="anchor"></a>

Class representing an activity that waits until a pin changes its state.

This class provides functionality to wait until a specified pin changes its state, either from LOW to HIGH or from HIGH to LOW.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `LowPowerStandbyType::UntilTimeElapsedClass` <a id="class_low_power_standby_type_1_1_until_time_elapsed_class" class="anchor"></a>

A class representing a time elapsed condition.

This class is used to specify a condition based on the elapsed time. It is typically used in conjunction with the LowPower library for Arduino.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

