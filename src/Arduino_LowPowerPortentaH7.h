/**
* @file
********************************************************************************
*                      Arduino_LowPowerPortentaH7 Library
*
*                 Copyright 2024 Arduino SA. http://arduino.cc
*
*                Original Author: A. Vidstrom (info@arduino.cc)
*
*         An API for the management of Sleep, Deep Sleep and Standby
*         Mode for the STM32H747 microcontroller on the Portenta H7
*
*                    SPDX-License-Identifier: MPL-2.0
*
*      This Source Code Form is subject to the terms of the Mozilla Public
*      License, v. 2.0. If a copy of the MPL was not distributed with this
*      file, you can obtain one at: http://mozilla.org/MPL/2.0/
*
********************************************************************************
*/

#ifndef LowPowerPortentaH7_H
#define LowPowerPortentaH7_H

/*
********************************************************************************
*                           Included header files
********************************************************************************
*/

#include <mbed.h>
#include <usb_phy_api.h>

/*
********************************************************************************
*                   Enumerations to be exposed to the sketch
********************************************************************************
*/

/**
 * @enum LowPowerReturnCode
 * @brief Provides the return codes for the API functions of the library.
 * The codes indicate the success or failure of the operations.
 */
enum class LowPowerReturnCode
{
    success,                    ///< The call was successful
    flashUnlockFailed,          ///< Unable to unlock flash to set option bytes
    obUnlockFailed,             ///< Unable to unlock option bytes before set
    obProgramFailed,            ///< Unable to program option bytes
    obLaunchFailed,             ///< Unable to reset board with new option bytes
    obNotPrepared,              ///< Option bytes not correct for Standby Mode
    m7StandbyFailed,            ///< M7 core unable to enter Standby Mode
    m4StandbyFailed,            ///< M4 core unable to enter Standby Mode
    wakeupDelayTooLong,         ///< RTC delay longer than supported by hardware
    enableLSEFailed,            ///< Unable to enable external 32 kHz oscillator
    selectLSEFailed,            ///< Unable to select external 32 kHz oscillator
    voltageScalingFailed,       ///< Unable to set appropriate voltage scaling
    turningOffEthernetFailed    ///< Unable to turn off Ethernet PHY chip
};

/**
 * @enum CPUMode
 * @brief Provides the different modes of the CPU.
 * Those can be used to determine in which mode the CPU was before waking up.
*/
enum class CPUMode
{
    d1DomainStandby,        ///< Standby mode for the D1 domain
    d2DomainStandby,        ///< Standby mode for the D2 domain
    standby,                ///< Standby mode for the whole microcontroller
    stop                    ///< Stop mode for the whole microcontroller
};

/*
********************************************************************************
*                                 Classes
********************************************************************************
*/

/**
 * @brief The LowPowerStandbyType class represents different methods of wakeup.
 * 
 * This class provides options for the following methods of wakeup: waiting until pin activity
 * or until a specified time has elapsed, or both.
 * Those are represented by LowPowerStandbyType::untilPinActivity and LowPowerStandbyType::untilTimeElapsed.
 * To combine the two options use the | operator.
 */
class LowPowerStandbyType {
    public:
        /// @cond DEV
        /**
         * @brief A class representing a wakeup option that waits until a wakeup pin changes its state.
         * 
         * This class provides functionality to wait until a specified pin changes its state,
         * from HIGH to LOW.
         */
        class UntilPinActivityClass {
        };
        /// @endcond

        /**
         * @brief Represents a wakeup option which waits until a pin activity occurs.
         * This allows the microcontroller to wake up from Standby Mode through a pin state
         * change triggered by external circuitry.
         */
        static const UntilPinActivityClass untilPinActivity;

        /// @cond DEV
        /**
         * @brief A class representing a time elapsed condition.
         * 
         * This class is used to specify a condition based on the elapsed time.
         */
        class UntilTimeElapsedClass {
        };
        /// @endcond

        /**
         * @brief Represents a wakeup option which waits until a specified time has elapsed.
        */
        static const UntilTimeElapsedClass untilTimeElapsed;

    private:

        /// @cond DEV
        /**
         * @brief Represents a wakeup option which waits until either 
         * a pin activity occurs or a specified time has elapsed, whichever happens first
        */
        class UntilEitherClass {
        };
        /// @endcond

        friend LowPowerStandbyType::UntilEitherClass operator|(
            const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity,
            const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed);

        friend LowPowerStandbyType::UntilEitherClass operator|(
            const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed,
            const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity);
};

/**
 * @brief The RTCWakeupDelay class represents a delay before waking up from Standby Mode.
*/
class RTCWakeupDelay {
    public:
        /**
        * @brief Create a delay object for the RTC wakeup.
        * @param hours Hours to wait before wakeup.
        * @param minutes Minutes to wait before wakeup.
        * @param seconds Seconds to wait before wakeup.
        */
        RTCWakeupDelay(const unsigned long long int hours,
                       const unsigned long long int minutes,
                       const unsigned long long int seconds) :
            value(hours * 60 * 60 + minutes * 60 + seconds)
        {
        }

    private:
        // We don't really need this large type, but we must use this specific
        // type for user-defined literals to work.
        unsigned long long int value;

        /**
        * @brief Private constructor to create a delay object with a specific delay value.
        * @param delay The delay value in seconds.
        */
        RTCWakeupDelay(const unsigned long long int delay) : value(delay)
        {
        }

        friend RTCWakeupDelay operator""_s(const unsigned long long int seconds);
        friend RTCWakeupDelay operator""_min(const unsigned long long int minutes);
        friend RTCWakeupDelay operator""_h(const unsigned long long int hours);
        friend RTCWakeupDelay operator+(const RTCWakeupDelay d1,
                                        const RTCWakeupDelay d2);

        friend class LowPowerPortentaH7;
};

/**
 * @class LowPowerPortentaH7
 * @brief A class that provides low power functionality for the Portenta H7 board.
 * 
 * The LowPowerPortentaH7 class allows the microcontroller on the Portenta H7 board
 * to enter low power modes such as Standby Mode and Deep Sleep Mode. It provides
 * functions to check the mode before startup, prepare the option bytes for entering Standby Mode,
 * and control the M4 and M7 cores independently. It also provides functions to measure
 * the time since boot, time spent in Idle, Sleep, and Deep Sleep modes.
 * 
 * This class is a singleton and shall always be accessed through the global LowPower object.
 * 
 * @note This class is specific to the Portenta H7 board.
 */
class LowPowerPortentaH7 {
    private:
        LowPowerPortentaH7()    = default;
        ~LowPowerPortentaH7()   = default;

        bool turnOffEthernet() const;
        void waitForFlashReady() const;

        /// @cond DEV

        // No delay argument, which is fine as long as the passed flag is
        // of UntilPinActivityClass
        template<typename U, typename...>
        struct ArgumentsAreCorrect {
            static constexpr bool value =
                std::is_same<U, LowPowerStandbyType::UntilPinActivityClass>::value;
        };

        // We got a delay argument, so make sure it's of the correct type, and
        // also make sure that the passed flag is of UntilTimeElapsedClass
        // or UntilEitherClass
        template<typename U, typename T>
        struct ArgumentsAreCorrect<U, T> {
            static constexpr bool value =
                ((std::is_same<T, RTCWakeupDelay>::value) && 
                ((std::is_same<U, LowPowerStandbyType::UntilTimeElapsedClass>::value) ||
                (std::is_same<U, LowPowerStandbyType::UntilEitherClass>::value)));
        };

        // One or more arguments passed after the delay, which is not ok
        template<typename U, typename T, typename... Args>
        struct ArgumentsAreCorrect<U, T, Args...> {
            static constexpr bool value = false;
        };

        /// @endcond

        // No delay argument passed, just return 0
        unsigned long long int passedWakeupDelay() const
        {
            return 0;
        }

        // Extract the delay argument if it is passed
        template<typename T, typename... Args>
        unsigned long long int passedWakeupDelay(T first, Args... others) const
        {
            return first.value;
        }

    public:

        /// @cond DEV
        /**
         * Returns the singleton instance of the LowPowerPortentaH7 class.
         * Due to the way the low power modes are configured, only one instance
         * of this class can exist at a time.
         *
         * @return The singleton instance of the LowPowerPortentaH7 class.
         */
        static LowPowerPortentaH7& getInstance() noexcept {
            static LowPowerPortentaH7 instance;
            return instance;
        }

        LowPowerPortentaH7(const LowPowerPortentaH7&)               = delete;
        LowPowerPortentaH7(LowPowerPortentaH7&&)                    = delete;

        LowPowerPortentaH7& operator=(const LowPowerPortentaH7&)    = delete;
        LowPowerPortentaH7& operator=(LowPowerPortentaH7&&)         = delete;
        /// @endcond

        /**
        * @brief Make Deep Sleep possible in the default case.
        */
        void allowDeepSleep() const;

        /**
        * @brief Check if Deep Sleep is possible or not at the moment.
        * @return Possible: true. Not possible: false.
        */
        bool canDeepSleep() const;

        /**
        * @brief Check if the option bytes are correct to enter Standby Mode.
        * @return A constant from the LowPowerReturnCode enum.
        */
        LowPowerReturnCode checkOptionBytes() const;

        /**
        * @brief Reset the flags that are used to determine the microcontroller's
        * previous CPU mode. This is necessary to get correct results from
        * wasInCPUMode().
        */
        void resetPreviousCPUModeFlags() const;


        // The deprecated attribute is used here because we only want this
        // warning to be shown if the user actually calls the function
        /**
        * @brief Check how many Deep Sleep locks are held at the moment.
        * @return The number held.
        */
       [[deprecated("This function is experimental and should not be used in production code")]]
        uint16_t numberOfDeepSleepLocks() const;

        /**
        * @brief Prepare the option bytes for entry into Standby Mode.
        * @return A constant from the LowPowerReturnCode enum.
        */
        LowPowerReturnCode prepareOptionBytes() const;

        /**
        * @brief Make the M4 core and D2 domain enter standby mode.
        * @return A constant from the LowPowerReturnCode enum.
        */
        LowPowerReturnCode standbyM4() const;

        // This is the variant that the compiler will see and use
        /// @cond DEV
        template<typename T, typename... Args>
        typename std::enable_if<ArgumentsAreCorrect<T, Args...>::value,
                 LowPowerReturnCode>::type
        standbyM7(const T standbyType, const Args... args) const;
        /// @endcond
        // This is the simplified variant that Doxygen will see and use
        // Notice that DOXYGEN_ONLY isn't defined anywhere - it doesn't
        // have to be since Doxygen is configured with ENABLE_PREPROCESSING NO
        #ifdef DOXYGEN_ONLY
        /**
        * @brief Make the M7 core and D1 domain enter standby mode, and make it possible for the D3 domain to do so too.
        * @param standbyType One or a combination of LowPowerStandbyType::untilPinActivity 
        * and LowPowerStandbyType::untilTimeElapsed. The combination is done with the | operator.
        * @param args An optional delay before waking up again, if LowPowerStandbyType::untilTimeElapsed is used.
        * @return A constant from the LowPowerReturnCode enum.
        */
        LowPowerReturnCode standbyM7(const T standbyType, const Args... args) const;
        #endif

        /**
        * @brief Time since the board was booted.
        * It reports the time since the last wake-up reset (after being in Standby Mode) 
        * or power-on depending on what happened last.
        * @return Number of microseconds.
        */
        uint64_t timeSinceBoot() const;

        /**
        * @brief Time spent in Idle Mode.
        * @return Number of microseconds.
        */
        uint64_t timeSpentIdle() const;

        /**
        * @brief Time spent in Sleep Mode.
        * @return Number of microseconds.
        */
        uint64_t timeSpentInSleep() const;

        /**
        * @brief Time spent in Deep Sleep Mode.
        * @return Number of microseconds.
        */
        uint64_t timeSpentInDeepSleep() const;

        /**
         * Checks if the microcontroller was in the given CPU mode before starting.
         * Note: It's possible that the microcontroller was in more than one of these modes
         * before starting. Call this function multiple times to check for each mode.
         * Important: When you're done checking, call resetStandbyModeFlags() to reset the flags
         * so they are reported correctly the next time the microcontroller starts.
         * @param mode The CPU mode to check.
         * @return True if the microcontroller was in the given mode, false otherwise.
         */
        bool wasInCPUMode(CPUMode mode) const;
};

/*
********************************************************************************
*                                   Externs
********************************************************************************
*/

/**
 * @brief The global LowPower singleton object provides access to low power features of the Portenta H7 board.
 */
extern const LowPowerPortentaH7& LowPower;

/*
********************************************************************************
*                           Overloaded operators
********************************************************************************
*/

/**
 * @brief Literals operator to add multiple delays together. e.g. 5_s + 10_min + 2_h
 * @param d1 The first delay.
 * @param d2 The second delay.
 * @return The sum of the two delays.
*/
RTCWakeupDelay operator+(const RTCWakeupDelay d1, const RTCWakeupDelay d2);

/**
 * @brief Literals operator to create a delay in seconds.
 * @param seconds The number of seconds to wait before waking up.
 * @return The delay object.
*/
RTCWakeupDelay operator""_s(const unsigned long long int seconds);

/**
 * @brief Literals operator to create a delay in minutes.
 * @param minutes The number of minutes to wait before waking up.
 * @return The delay object.
*/
RTCWakeupDelay operator""_min(const unsigned long long int minutes);

/**
 * @brief Literals operator to create a delay in hours.
 * @param hours The number of hours to wait before waking up.
 * @return The delay object.
*/
RTCWakeupDelay operator""_h(const unsigned long long int hours);

/**
 * @brief Operator to combine two wakeup options.
 * @param untilPinActivity The pin activity wakeup option.
 * @param untilTimeElapsed The time elapsed wakeup option.
 * @return The combined wakeup option.
*/
LowPowerStandbyType::UntilEitherClass operator|(
    const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity,
    const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed);

/**
 * @brief Operator to combine two wakeup options.
 * @param untilTimeElapsed The time elapsed wakeup option.
 * @param untilPinActivity The pin activity wakeup option.
 * @return The combined wakeup option.
*/
LowPowerStandbyType::UntilEitherClass operator|(
    const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed,
    const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity);

/*
********************************************************************************
*                           Template functions
********************************************************************************
*/

/// @cond DEV
template<typename T, typename... Args>
typename std::enable_if<LowPowerPortentaH7::ArgumentsAreCorrect<T, Args...>::value,
                        LowPowerReturnCode>::type
LowPowerPortentaH7::standbyM7(const T standbyType,
                              const Args... args) const
{
    const unsigned long long int wakeupDelay = passedWakeupDelay(args...);

    if (wakeupDelay >= (2ULL << 17))
    {
        return LowPowerReturnCode::wakeupDelayTooLong;
    }

    // Ethernet must be turned off before we enter Standby Mode, because
    // otherwise, the Ethernet transmit termination resistors will overheat
    // from the voltage that gets applied over them. It would be 125 mW in each
    // of them, while they are rated at 50 mW. If we fail to turn off Ethernet,
    // we must not proceed. If this library is used with another library that
    // turns off the rail that powers the Ethernet chip before calling this
    // function, that library should #define NO_ETHERNET_TURN_OFF, or entering
    // Standby Mode will fail. Anyone who defines that constant takes
    // responsibility for not overheating the resistors. It is NOT part of the
    // API intended for ordinary users.
    #ifdef NO_ETHERNET_TURN_OFF
        #warning "If you are defining NO_ETHERNET_TURN_OFF in your own sketch \
or library, then please make sure to turn off the power \
to the Ethernet chip before going into Standby Mode."
    #else
        if (false == turnOffEthernet())
        {
            return LowPowerReturnCode::turningOffEthernetFailed;
        }
    #endif

    // Prevent Mbed from changing things
    core_util_critical_section_enter();

    waitForFlashReady();

    // Make the D3 domain follow the CPU subsystem modes. This also applies to
    // Standby Mode according to the Reference Manual, even though the constant
    // is called PWR_D3_DOMAIN_STOP.
    HAL_PWREx_ConfigD3Domain(PWR_D3_DOMAIN_STOP);

    // Make sure that the voltage scaling isn't in VOS0 by setting it to VOS1.
    // While troubleshooting, change this to PWR_REGULATOR_VOLTAGE_SCALE3 to
    // better differentiate the states of the uC while measuring VCORE at the
    // VCAP pins.
    if (HAL_OK != HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1))
    {
        return LowPowerReturnCode::voltageScalingFailed;
    }

    // Clear all but the reserved bits in these registers to mask out external
    // interrupts -->
    EXTI->IMR1 = 0;
    // Bit 13 in IMR2 is reserved and must always be 1
    EXTI->IMR2 = 1 << 13;
    // Bits 31:25, 19, and 18 in IMR3 are reserved and must be preserved
    EXTI->IMR3 &= ~0x1f5ffff;
    // <--

    if ((std::is_same<LowPowerStandbyType::UntilPinActivityClass, T>::value) ||
       (std::is_same<LowPowerStandbyType::UntilEitherClass, T>::value))
    {
        // Enable the GPIO 0 wakeup pin in IMR
        HAL_EXTI_D1_EventInputConfig(EXTI_LINE58, EXTI_MODE_IT, ENABLE);
    }
    if ((std::is_same<LowPowerStandbyType::UntilTimeElapsedClass, T>::value) ||
       (std::is_same<LowPowerStandbyType::UntilEitherClass, T>::value))
    {
        // Enable RTC wakeup in IMR
        HAL_EXTI_D1_EventInputConfig(EXTI_LINE19, EXTI_MODE_IT, ENABLE);
    }

    // Set all but the reserved bits in these registers to clear pending
    // external interrupts -->
    // Bits 31:22 in PR1 are reserved and the original value must be preserved
    EXTI->PR1 |= 0x3fffff;
    // All bits except 17 and 19 in PR2 are reserved and the original value must
    // be preserved
    EXTI->PR2 |= ((1 << 17) | (1 << 19));
    // All bits except 18, 20, 21, and 22 in PR3 are reserved and the original
    // value must be preserved
    EXTI->PR3 |= ((1 << 18) | (1 << 20) | (1 << 21) | (1 << 22));
    // <--

    if ((std::is_same<LowPowerStandbyType::UntilPinActivityClass, T>::value) ||
       (std::is_same<LowPowerStandbyType::UntilEitherClass, T>::value))
    {
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN1);
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN2);
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN3);
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN4);
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN5);
        HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN6);

        HAL_PWREx_ClearWakeupFlag(PWR_WAKEUP_FLAG_ALL);

        PWREx_WakeupPinTypeDef wakeUpPinConfiguration{};
         // PWR_WAKEUP_PIN4 = Portenta Breakout Board GPIO 0
        wakeUpPinConfiguration.WakeUpPin = PWR_WAKEUP_PIN4;
        // Internal pull-up enabled, and the board's GPIO 0 pin must be
        // pulled low to wake up the uC. There were some early problems during
        // development where the uC didn't wake up when the internal pull-up
        // was used. What worked then was to use PWR_PIN_NO_PULL together with
        // a 4.7 kohm external pull-up resistor (no particular reason for that
        // exact value). Hopefully the internal pull-up will keep on working.
        wakeUpPinConfiguration.PinPolarity = PWR_PIN_POLARITY_LOW;
        wakeUpPinConfiguration.PinPull = PWR_PIN_PULL_UP;
        HAL_PWREx_EnableWakeUpPin(&wakeUpPinConfiguration);
    }

    if ((std::is_same<LowPowerStandbyType::UntilTimeElapsedClass, T>::value) ||
       (std::is_same<LowPowerStandbyType::UntilEitherClass, T>::value))
    {
        RCC_OscInitTypeDef oscInit{};
        oscInit.OscillatorType = RCC_OSCILLATORTYPE_LSE;
        oscInit.LSEState = RCC_LSE_ON;
        if (HAL_OK != HAL_RCC_OscConfig(&oscInit))
        {
            return LowPowerReturnCode::enableLSEFailed;
        }

        RCC_PeriphCLKInitTypeDef periphClkInit{};
        periphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        periphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        if (HAL_OK != HAL_RCCEx_PeriphCLKConfig(&periphClkInit))
        {
            return LowPowerReturnCode::selectLSEFailed;
        }

        // This enables the RTC. It must not be called before the RTC input
        // clock source is selected above.
        __HAL_RCC_RTC_ENABLE();

        LL_RTC_DisableWriteProtection(RTC);

        // Enter init mode. We're doing this at the register level because of
        // a bug in the LL that ships with the current version of Mbed, where,
        // among other things, reserved bits are overwritten. Bit 7 is the INIT
        // bit.
        RTC->ISR |= 1 << 7;
        while (1U != LL_RTC_IsActiveFlag_INIT(RTC))
            ;

        LL_RTC_SetHourFormat(RTC, LL_RTC_HOURFORMAT_24HOUR);
        // LSE at 32767 Hz / (127+1) / (255 + 1) = 1 Hz for the RTC
        LL_RTC_SetAsynchPrescaler(RTC, 127);
        LL_RTC_SetSynchPrescaler(RTC, 255);

        // Exit init mode
        RTC->ISR &= ~(1 << 7);
        // This is probably not necessary, but included just in case
        while (0U != LL_RTC_IsActiveFlag_INIT(RTC))
            ;

        LL_RTC_DisableIT_WUT(RTC);
        LL_RTC_WAKEUP_Disable(RTC);
        while (1 != LL_RTC_IsActiveFlag_WUTW(RTC))
            ;

        if (wakeupDelay < (2ULL << 16)) {
            LL_RTC_WAKEUP_SetAutoReload(RTC, wakeupDelay);
            LL_RTC_WAKEUP_SetClock(RTC, LL_RTC_WAKEUPCLOCK_CKSPRE);
        }
        else {
            LL_RTC_WAKEUP_SetAutoReload(RTC, wakeupDelay - (2ULL << 16));
            LL_RTC_WAKEUP_SetClock(RTC, LL_RTC_WAKEUPCLOCK_CKSPRE_WUT);
        }

        LL_RTC_WAKEUP_Enable(RTC);
        LL_RTC_EnableIT_WUT(RTC);
        __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();
        LL_RTC_ClearFlag_WUT(RTC);

        LL_RTC_EnableWriteProtection(RTC);
    }

    // Set all but the reserved bits in these registers to clear pending
    // interrupts -->
    // Bits 31:22 in PR1 are reserved and the original value must be preserved
    EXTI->PR1 |= 0x3fffff;
    // All bits except 17 and 19 in PR2 are reserved and the original value must
    // be preserved
    EXTI->PR2 |= ((1 << 17) | (1 << 19));
    // All bits except 18, 20, 21, and 22 in PR3 are reserved and the original
    // value must be preserved
    EXTI->PR3 |= ((1 << 18) | (1 << 20) | (1 << 21) | (1 << 22));
    // <--

    // Disable and clear all pending interrupts in the NVIC. There are 8
    // registers in the Cortex-M7.
    for (auto i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xffffffff;
        NVIC->ICPR[i] = 0xffffffff;
    }

    if ((std::is_same<LowPowerStandbyType::UntilTimeElapsedClass, T>::value) ||
       (std::is_same<LowPowerStandbyType::UntilEitherClass, T>::value))
    {
        HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x0, 0);
        HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
    }

    // When we reset the peripherals below, the OSCEN line will no longer enable
    // the MEMS oscillator for the HSE. This creates a race condition, where the
    // HSE sometimes stops before we enter Standby Mode, and sometimes keeps
    // going until Standby Mode is reached. If the HSE stops before Standby
    // Mode is reached, the STM32H747 goes into a frozen state where the SMPS
    // step-down converter never enters OPEN mode, the LDO voltage regulator
    // stays on, and NRST stops working. One solution to this is to enable the
    // Clock Security System (CSS), which makes the uC automatically switch over
    // to HSI when it detects an HSE failure. It also triggers an NMI, which
    // must be handled correctly.
    HAL_RCC_EnableCSS();

    // Reset peripherals to prepare for entry into Standby Mode
    __HAL_RCC_AHB3_FORCE_RESET();
    __HAL_RCC_AHB3_RELEASE_RESET();
    __HAL_RCC_AHB1_FORCE_RESET();
    __HAL_RCC_AHB1_RELEASE_RESET();
    __HAL_RCC_AHB2_FORCE_RESET();
    __HAL_RCC_AHB2_RELEASE_RESET();
    __HAL_RCC_APB3_FORCE_RESET();
    __HAL_RCC_APB3_RELEASE_RESET();
    __HAL_RCC_APB1L_FORCE_RESET();
    __HAL_RCC_APB1L_RELEASE_RESET();
    __HAL_RCC_APB1H_FORCE_RESET();
    __HAL_RCC_APB1H_RELEASE_RESET();
    __HAL_RCC_APB2_FORCE_RESET();
    __HAL_RCC_APB2_RELEASE_RESET();
    __HAL_RCC_APB4_FORCE_RESET();
    __HAL_RCC_APB4_RELEASE_RESET();
    __HAL_RCC_AHB4_FORCE_RESET();
    __HAL_RCC_AHB4_RELEASE_RESET();

    // Make sure that the M7 core takes the M4 core's state into account before
    // turning off the power to the flash memory. The normal way to do this
    // would be with __HAL_RCC_FLASH_C2_ALLOCATE(), but there's a bug in GCC
    // versions before 7.5.0, where the load instruction may sometimes be
    // discarded when a volatile variable is cast to void and there are extra
    // parentheses around the volatile variable's name. Extra parentheses should
    // not make a difference - see the C++14 standard, section 5, paragraph 11
    // - but we are currently running GCC 7.2.1. The data synchronization
    // barrier instruction below replaces the void-casted register read in
    // __HAL_RCC_FLASH_C2_ALLOCATE().
    RCC_C2->AHB3ENR |= RCC_AHB3ENR_FLASHEN;
    __DSB();

    // Clean the entire data cache if we're running on the M7 core. We must
    // make sure we're compiling for the CM7 core with conditional compilation,
    // or we won't get this through the first phase of template compilation.
#if defined CORE_CM7
    SCB_CleanDCache();
#endif

    HAL_PWREx_EnterSTANDBYMode(PWR_D1_DOMAIN);

    return LowPowerReturnCode::m7StandbyFailed;
}
/// @endcond

#endif  // End of header guard
