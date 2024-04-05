# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`LowPowerPortentaH7`](#class_low_power_portenta_h7) | 
`class ` [`LowPowerStandbyType`](#class_low_power_standby_type) | 
`class ` [`RTCWakeupDelay`](#class_r_t_c_wakeup_delay) | 
`class ` [`LowPowerStandbyType::UntilEitherClass`](#class_low_power_standby_type_1_1_until_either_class) | 
`class ` [`LowPowerStandbyType::UntilPinActivityClass`](#class_low_power_standby_type_1_1_until_pin_activity_class) | 
`class ` [`LowPowerStandbyType::UntilTimeElapsedClass`](#class_low_power_standby_type_1_1_until_time_elapsed_class) | 
`struct ` [`LowPowerPortentaH7::ArgumentsAreCorrect`](#struct_low_power_portenta_h7_1_1_arguments_are_correct) | 
`struct ` [`LowPowerPortentaH7::ArgumentsAreCorrect< U, T >`](#struct_low_power_portenta_h7_1_1_arguments_are_correct_3_01_u_00_01_t_01_4) | 
`struct ` [`LowPowerPortentaH7::ArgumentsAreCorrect< U, T, Args... >`](#struct_low_power_portenta_h7_1_1_arguments_are_correct_3_01_u_00_01_t_00_01_args_8_8_8_01_4) | 

# class `LowPowerPortentaH7` <a id="class_low_power_portenta_h7" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`LowPowerPortentaH7`](#class_low_power_portenta_h7_1af7fac6e5697576795570e4962911ece1) |  |
| [`LowPowerPortentaH7`](#class_low_power_portenta_h7_1ad36171462fa9a3c84abc3ea616574b31) |  |
| [`operator=`](#class_low_power_portenta_h7_1a0459931bef15d942402ed736545cb37e) |  |
| [`operator=`](#class_low_power_portenta_h7_1a2b11ffce1fe9f1b57caa92b22c921ed0) |  |
| [`allowDeepSleep`](#class_low_power_portenta_h7_1a7ed518f8205a0b7306d23b7e2a22e82b) | Make Deep Sleep possible in the default case. |
| [`canDeepSleep`](#class_low_power_portenta_h7_1a07d9e0f356e40ac70655e279fbad87a9) | Check if Deep Sleep is possible or not at the moment. |
| [`checkOptionBytes`](#class_low_power_portenta_h7_1a7519d3acf693f450af84312576d8e669) | Check if the option bytes are correct to enter Standby Mode. |
| [`modeWasD1Standby`](#class_low_power_portenta_h7_1a4eb99fd03e8891f93d43aca4ea2329f9) | Check if the D1 domain was in Standby Mode or not. |
| [`modeWasD2Standby`](#class_low_power_portenta_h7_1a81e1c97f6411de6c6df390f7cb1ef8dc) | Check if the D2 domain was in Standby Mode or not. |
| [`modeWasStandby`](#class_low_power_portenta_h7_1afb2fc28d8a59bc34799e4c83a746f7c4) | Check if the whole microcontroller was in Standby Mode or not. |
| [`modeWasStop`](#class_low_power_portenta_h7_1a8420caa1148e61bc4d40e9627866afe3) | Check if the whole microcontroller was in Stop Mode or not. |
| [`__attribute__`](#class_low_power_portenta_h7_1ae9b5f1b182da16b7aff3945c0f5e2718) | Check how many Deep Sleep locks are held at the moment. |
| [`prepareOptionBytes`](#class_low_power_portenta_h7_1abdc0ce13b68d3a2188702690997af2ae) | Prepare the option bytes for entry into Standby Mode. |
| [`resetPreviousMode`](#class_low_power_portenta_h7_1a6f09b3ffe26355372f287ab90a451cc2) | Reset the flags behind the modeWas...() functions. |
| [`standbyM4`](#class_low_power_portenta_h7_1a9e07fd4f7895a7753e7e28f99aca1ace) | Make the M4 core enter Standby Mode. |
| [`standbyM7`](#class_low_power_portenta_h7_1a1eb5cec6e9604a48074f1c10ef5e7fb0) | Make the M7 core enter Standby Mode. |
| [`timeSinceBoot`](#class_low_power_portenta_h7_1a4758c25574b6d099545ac8d55eff6f68) | Time since the board was booted. |
| [`timeSpentIdle`](#class_low_power_portenta_h7_1ad42fdfa6885d8e0fdca5aa012fdb4c60) | Time spent in idle. |
| [`timeSpentInSleep`](#class_low_power_portenta_h7_1a994eb6fcc0382515a82b81fa37ca9f3c) | Time spent in Sleep Mode. |
| [`timeSpentInDeepSleep`](#class_low_power_portenta_h7_1a146eb61800a74360687fd34b456c0b44) | Time spent in Deep Sleep Mode. |
| [`getInstance`](#class_low_power_portenta_h7_1aa852067ffc101c0cb7ac526cc91080b4) |  |

## Members

### `LowPowerPortentaH7` <a id="class_low_power_portenta_h7_1af7fac6e5697576795570e4962911ece1" class="anchor"></a>

```cpp
LowPowerPortentaH7(const LowPowerPortentaH7 &) = delete
```

<hr />

### `LowPowerPortentaH7` <a id="class_low_power_portenta_h7_1ad36171462fa9a3c84abc3ea616574b31" class="anchor"></a>

```cpp
LowPowerPortentaH7( LowPowerPortentaH7 &&) = delete
```

<hr />

### `operator=` <a id="class_low_power_portenta_h7_1a0459931bef15d942402ed736545cb37e" class="anchor"></a>

```cpp
LowPowerPortentaH7 & operator=(const LowPowerPortentaH7 &) = delete
```

<hr />

### `operator=` <a id="class_low_power_portenta_h7_1a2b11ffce1fe9f1b57caa92b22c921ed0" class="anchor"></a>

```cpp
LowPowerPortentaH7 & operator=( LowPowerPortentaH7 &&) = delete
```

<hr />

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

### `__attribute__` <a id="class_low_power_portenta_h7_1ae9b5f1b182da16b7aff3945c0f5e2718" class="anchor"></a>

```cpp
__attribute__((deprecated("The numberOfDeepSleepLocks() function" " is experimental and should not be used in production code"))) const
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
* `standbyType` One or a combination of LowPowerStandbyType::untilPinActivity and LowPowerStandbyType::untilTimeElapsed. 

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

<hr />

# class `LowPowerStandbyType` <a id="class_low_power_standby_type" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `RTCWakeupDelay` <a id="class_r_t_c_wakeup_delay" class="anchor"></a>

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

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `LowPowerStandbyType::UntilPinActivityClass` <a id="class_low_power_standby_type_1_1_until_pin_activity_class" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `LowPowerStandbyType::UntilTimeElapsedClass` <a id="class_low_power_standby_type_1_1_until_time_elapsed_class" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `LowPowerPortentaH7::ArgumentsAreCorrect` <a id="struct_low_power_portenta_h7_1_1_arguments_are_correct" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `LowPowerPortentaH7::ArgumentsAreCorrect< U, T >` <a id="struct_low_power_portenta_h7_1_1_arguments_are_correct_3_01_u_00_01_t_01_4" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `LowPowerPortentaH7::ArgumentsAreCorrect< U, T, Args... >` <a id="struct_low_power_portenta_h7_1_1_arguments_are_correct_3_01_u_00_01_t_00_01_args_8_8_8_01_4" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

