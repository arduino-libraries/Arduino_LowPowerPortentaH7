# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`LowPowerPortentaH7`](#class_low_power_portenta_h7) | A class that provides low power functionality for the Portenta H7 board.
`class ` [`LowPowerStandbyType`](#class_low_power_standby_type) | The [LowPowerStandbyType](#class_low_power_standby_type) class represents different methods of wakeup.
`class ` [`RTCWakeupDelay`](#class_r_t_c_wakeup_delay) | The [RTCWakeupDelay](#class_r_t_c_wakeup_delay) class represents a delay before waking up from Standby Mode.

# class `LowPowerPortentaH7` <a id="class_low_power_portenta_h7" class="anchor"></a>

A class that provides low power functionality for the Portenta H7 board.

The [LowPowerPortentaH7](#class_low_power_portenta_h7) class allows the microcontroller on the Portenta H7 board to enter low power modes such as Standby Mode and Deep Sleep Mode. It provides functions to check the mode before startup, prepare the option bytes for entering Standby Mode, and control the M4 and M7 cores independently. It also provides functions to measure the time since boot, time spent in Idle, Sleep, and Deep Sleep modes.

This class is a singleton and shall always be accessed through the global LowPower object.

This class is specific to the Portenta H7 board.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`allowDeepSleep`](#class_low_power_portenta_h7_1a7ed518f8205a0b7306d23b7e2a22e82b) | Make Deep Sleep possible in the default case. |
| [`canDeepSleep`](#class_low_power_portenta_h7_1a07d9e0f356e40ac70655e279fbad87a9) | Check if Deep Sleep is possible or not at the moment. |
| [`checkOptionBytes`](#class_low_power_portenta_h7_1a7519d3acf693f450af84312576d8e669) | Check if the option bytes are correct to enter Standby Mode. |
| [`resetPreviousCPUModeFlags`](#class_low_power_portenta_h7_1a1753e3c053b2b64b59da3cbb9b921d76) | Reset the flags that are used to determine the microcontroller's previous CPU mode. This is necessary to get correct results from [wasInCPUMode()](#class_low_power_portenta_h7_1ae2059eb4fb01a30342b9fb6918b6ab4c). |
| [`numberOfDeepSleepLocks`](#class_low_power_portenta_h7_1a9d2730d86abf42782261b0f03778c3bb) | Check how many Deep Sleep locks are held at the moment. |
| [`prepareOptionBytes`](#class_low_power_portenta_h7_1abdc0ce13b68d3a2188702690997af2ae) | Prepare the option bytes for entry into Standby Mode. |
| [`standbyM4`](#class_low_power_portenta_h7_1a9e07fd4f7895a7753e7e28f99aca1ace) | Make the M4 core and D2 domain enter standby mode. |
| [`standbyM7`](#class_low_power_portenta_h7_1aa9c1cb86c832c35f6653a3d6c9f0d32f) | Make the M7 core and D1 domain enter standby mode, and make it possible for the D3 domain to do so too. |
| [`timeSinceBoot`](#class_low_power_portenta_h7_1a4758c25574b6d099545ac8d55eff6f68) | Time since the board was booted. It reports the time since the last wake-up reset (after being in Standby Mode) or power-on depending on what happened last. |
| [`timeSpentIdle`](#class_low_power_portenta_h7_1ad42fdfa6885d8e0fdca5aa012fdb4c60) | Time spent in Idle Mode. |
| [`timeSpentInSleep`](#class_low_power_portenta_h7_1a994eb6fcc0382515a82b81fa37ca9f3c) | Time spent in Sleep Mode. |
| [`timeSpentInDeepSleep`](#class_low_power_portenta_h7_1a146eb61800a74360687fd34b456c0b44) | Time spent in Deep Sleep Mode. |
| [`wasInCPUMode`](#class_low_power_portenta_h7_1ae2059eb4fb01a30342b9fb6918b6ab4c) | Checks if the microcontroller was in the given CPU mode before starting. Note: It's possible that the microcontroller was in more than one of these modes before starting. Call this function multiple times to check for each mode. Important: When you're done checking, call resetStandbyModeFlags() to reset the flags so they are reported correctly the next time the microcontroller starts.  |

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

### `resetPreviousCPUModeFlags` <a id="class_low_power_portenta_h7_1a1753e3c053b2b64b59da3cbb9b921d76" class="anchor"></a>

```cpp
void resetPreviousCPUModeFlags() const
```

Reset the flags that are used to determine the microcontroller's previous CPU mode. This is necessary to get correct results from [wasInCPUMode()](#class_low_power_portenta_h7_1ae2059eb4fb01a30342b9fb6918b6ab4c).

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

### `standbyM4` <a id="class_low_power_portenta_h7_1a9e07fd4f7895a7753e7e28f99aca1ace" class="anchor"></a>

```cpp
LowPowerReturnCode standbyM4() const
```

Make the M4 core and D2 domain enter standby mode.

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `standbyM7` <a id="class_low_power_portenta_h7_1aa9c1cb86c832c35f6653a3d6c9f0d32f" class="anchor"></a>

```cpp
LowPowerReturnCode standbyM7(const T standbyType, const Args... args) const
```

Make the M7 core and D1 domain enter standby mode, and make it possible for the D3 domain to do so too.

#### Parameters
* `standbyType` One or a combination of [LowPowerStandbyType::untilPinActivity](#class_low_power_standby_type_1a4c5b50ac615cf60ff88dd3b9bb145fa9) and [LowPowerStandbyType::untilTimeElapsed](#class_low_power_standby_type_1aa4882e571c0e9444c5978c8520e8e90e). The combination is done with the | operator. 

* `args` An optional delay before waking up again, if [LowPowerStandbyType::untilTimeElapsed](#class_low_power_standby_type_1aa4882e571c0e9444c5978c8520e8e90e) is used. 

#### Returns
A constant from the LowPowerReturnCode enum.
<hr />

### `timeSinceBoot` <a id="class_low_power_portenta_h7_1a4758c25574b6d099545ac8d55eff6f68" class="anchor"></a>

```cpp
uint64_t timeSinceBoot() const
```

Time since the board was booted. It reports the time since the last wake-up reset (after being in Standby Mode) or power-on depending on what happened last.

#### Returns
Number of microseconds.
<hr />

### `timeSpentIdle` <a id="class_low_power_portenta_h7_1ad42fdfa6885d8e0fdca5aa012fdb4c60" class="anchor"></a>

```cpp
uint64_t timeSpentIdle() const
```

Time spent in Idle Mode.

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

### `wasInCPUMode` <a id="class_low_power_portenta_h7_1ae2059eb4fb01a30342b9fb6918b6ab4c" class="anchor"></a>

```cpp
bool wasInCPUMode( CPUMode mode) const
```

Checks if the microcontroller was in the given CPU mode before starting. Note: It's possible that the microcontroller was in more than one of these modes before starting. Call this function multiple times to check for each mode. Important: When you're done checking, call resetStandbyModeFlags() to reset the flags so they are reported correctly the next time the microcontroller starts. 
#### Parameters
* `mode` The CPU mode to check. 

#### Returns
True if the microcontroller was in the given mode, false otherwise.
<hr />

# class `LowPowerStandbyType` <a id="class_low_power_standby_type" class="anchor"></a>

The [LowPowerStandbyType](#class_low_power_standby_type) class represents different methods of wakeup.

This class provides options for the following methods of wakeup: waiting until pin activity or until a specified time has elapsed, or both. Those are represented by [LowPowerStandbyType::untilPinActivity](#class_low_power_standby_type_1a4c5b50ac615cf60ff88dd3b9bb145fa9) and [LowPowerStandbyType::untilTimeElapsed](#class_low_power_standby_type_1aa4882e571c0e9444c5978c8520e8e90e). To combine the two options use the | operator.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `RTCWakeupDelay` <a id="class_r_t_c_wakeup_delay" class="anchor"></a>

The [RTCWakeupDelay](#class_r_t_c_wakeup_delay) class represents a delay before waking up from Standby Mode.

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

