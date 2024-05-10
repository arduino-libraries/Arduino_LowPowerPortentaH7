/*
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

/*
********************************************************************************
*                           Included header files
********************************************************************************
*/

#include "Arduino_LowPowerPortentaH7.h"
#include "lan8742.h"

/*
********************************************************************************
*                               NMI handling
********************************************************************************
*/

extern "C" void NMI_Handler(void)
{
    // Make sure that the NMI doesn't trigger again and again when the HSE
    // clock has failed. If there's some other kind of NMI, we want to enter an
    // infinite loop. But we can't check the RCC_CIFR_HSECSSF flag in RCC->CIFR,
    // because there seems to be a problem with the uC where it sometimes
    // triggers an NMI for HSE failure without setting the flag. Then we would
    // go into an infinite loop by mistake, so we just check RCC_CR_CSSHSEON
    // instead.
    if ((RCC->CR) & RCC_CR_CSSHSEON)
    {
        LL_RCC_ClearFlag_HSECSS();
    }
    else
    {
        for ( ; ; )
        {
            // See the C++11 standard 1.10 point 24 (as well as point 1 for
            // implementations with only one thread of execution still being
            // considered executing a thread)
            volatile int dummy = 0;
            (void) dummy;
        }
    }
}

/*
********************************************************************************
*                           Overloaded operators
********************************************************************************
*/

RTCWakeupDelay operator+(const RTCWakeupDelay d1, const RTCWakeupDelay d2)
{
    return RTCWakeupDelay(d1.value + d2.value);
}

RTCWakeupDelay operator""_s(const unsigned long long int seconds)
{
    return RTCWakeupDelay(seconds);
}

RTCWakeupDelay operator""_min(const unsigned long long int minutes)
{
    return RTCWakeupDelay(minutes * 60);
}

RTCWakeupDelay operator""_h(const unsigned long long int hours)
{
    return RTCWakeupDelay(hours * 60 * 60);
}

LowPowerStandbyType::UntilEitherClass operator|(
    const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity,
    const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed)
{
    return LowPowerStandbyType::UntilEitherClass();
}

LowPowerStandbyType::UntilEitherClass operator|(
    const LowPowerStandbyType::UntilTimeElapsedClass& untilTimeElapsed,
    const LowPowerStandbyType::UntilPinActivityClass& untilPinActivity)
{
    return LowPowerStandbyType::UntilEitherClass();
}

/*
********************************************************************************
*                              Instantiations
********************************************************************************
*/

const LowPowerStandbyType::UntilPinActivityClass
    LowPowerStandbyType::untilPinActivity{};

const LowPowerStandbyType::UntilTimeElapsedClass
    LowPowerStandbyType::untilTimeElapsed{};

const LowPowerPortentaH7& LowPower = LowPowerPortentaH7::getInstance();

/*
********************************************************************************
*        Unnamed namespace for library-internal functions and variables
********************************************************************************
*/

namespace {

ETH_HandleTypeDef ethHandle;

int32_t ETH_PHY_IO_Init()
{
    HAL_ETH_SetMDIOClockRange(&ethHandle);
    return 0;
}

int32_t ETH_PHY_IO_DeInit()
{
  return 0;
}

int32_t ETH_PHY_IO_ReadReg(uint32_t devAddr, uint32_t regAddr, uint32_t *pRegVal)
{
  if (HAL_OK != HAL_ETH_ReadPHYRegister(&ethHandle, devAddr, regAddr, pRegVal))
  {
    return -1;
  }
  return 0;
}

int32_t ETH_PHY_IO_WriteReg(uint32_t devAddr, uint32_t regAddr, uint32_t regVal)
{
  if (HAL_OK != HAL_ETH_WritePHYRegister(&ethHandle, devAddr, regAddr, regVal))
  {
    return -1;
  }
  return 0;
}

int32_t ETH_PHY_IO_GetTick()
{
  return HAL_GetTick();
}

lan8742_Object_t LAN8742;

lan8742_IOCtx_t  LAN8742_IOCtx = {
    ETH_PHY_IO_Init,
    ETH_PHY_IO_DeInit,
    ETH_PHY_IO_WriteReg,
    ETH_PHY_IO_ReadReg,
    ETH_PHY_IO_GetTick
};

}   // End of unnamed namespace

/*
********************************************************************************
*                             Member functions
********************************************************************************
*/

void LowPowerPortentaH7::allowDeepSleep() const
{
  // Turn off USB
  USBPhy * const phy = get_usb_phy();
  phy->deinit();
  // Turn off the micros() timer
  getTimer(TIMER).stop();
}

bool LowPowerPortentaH7::canDeepSleep() const
{
    return sleep_manager_can_deep_sleep();
}

LowPowerReturnCode LowPowerPortentaH7::checkOptionBytes() const
{
    FLASH_OBProgramInitTypeDef flashOBProgramInit{};

    flashOBProgramInit.Banks = FLASH_BANK_1;
    HAL_FLASHEx_OBGetConfig(&flashOBProgramInit);
    if (OB_STDBY_RST_D1 & flashOBProgramInit.USERConfig)
    {
        return LowPowerReturnCode::obNotPrepared;
    }
    if (OB_STDBY_RST_D2 & flashOBProgramInit.USERConfig)
    {
        return LowPowerReturnCode::obNotPrepared;
    }
    if (OB_BCM4_ENABLE & flashOBProgramInit.USERConfig)
    {
        return LowPowerReturnCode::obNotPrepared;
    }
    return LowPowerReturnCode::success;
}

void LowPowerPortentaH7::resetPreviousCPUModeFlags() const
{
    PWR->CPUCR |= PWR_CPUCR_CSSF;
}

uint16_t LowPowerPortentaH7::numberOfDeepSleepLocks() const
{
    // This function uses undocumented features of Mbed to retrieve the number
    // of active deep sleep locks. It is experimental and may break at any time,
    // but can be handy for some users to debug deep sleep lock problems.
    // It uses features of the compiled machine code to find the number of locks.
    
    // clang-format off
    return *((volatile uint16_t*) *((volatile uint32_t*) ((((volatile uint32_t)
            &sleep_manager_can_deep_sleep) & 0xfffffffe) + 0x10)));
    // clang-format on
}

LowPowerReturnCode LowPowerPortentaH7::prepareOptionBytes() const
{
    FLASH_OBProgramInitTypeDef flashOBProgramInit{};

    flashOBProgramInit.Banks        = FLASH_BANK_1;
    flashOBProgramInit.OptionType   = OPTIONBYTE_USER;
    flashOBProgramInit.USERType     = OB_USER_NRST_STDBY_D1 |
                                      OB_USER_NRST_STDBY_D2 |
                                      OB_USER_BCM4;
    flashOBProgramInit.USERConfig   = OB_STDBY_NO_RST_D1 |
                                      OB_STDBY_NO_RST_D2 |
                                      OB_BCM4_DISABLE;
    if (HAL_OK != HAL_FLASH_Unlock())
    {
        return LowPowerReturnCode::flashUnlockFailed;
    }
    if (HAL_OK != HAL_FLASH_OB_Unlock())
    {
        return LowPowerReturnCode::obUnlockFailed;
    }
    if (HAL_OK != HAL_FLASHEx_OBProgram(&flashOBProgramInit))
    {
        HAL_FLASH_OB_Lock();
        HAL_FLASH_Lock();
        return LowPowerReturnCode::obProgramFailed;
    }
    HAL_FLASH_OB_Launch();
    // The board should reset at this point, so anything beyond this point
    // is a failure
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    return LowPowerReturnCode::obLaunchFailed;
}

LowPowerReturnCode LowPowerPortentaH7::standbyM4() const
{
    // Prevent Mbed from changing things
    core_util_critical_section_enter();

    waitForFlashReady();

    // Clear all but the reserved bits in these registers to mask out external
    // interrupts -->
    EXTI->C2IMR1 = 0;
    // Bit 13 of IMR is reserved and must always be 1
    EXTI->C2IMR2 = 1 << 13;
    // Bits 31:25, 19, and 18 of IMR are reserved and must be preserved
    EXTI->C2IMR3 &= ~0x1f5ffff;
    // <--

    // Set all but the reserved bits in these registers to clear pending
    // external interrupts -->
    // Bits 31:22 in PR1 are reserved and the original value must be preserved
    EXTI->C2PR1 |= 0x3fffff;
    // All bits except 17 and 19 in PR2 are reserved and the original value must
    // be preserved
    EXTI->C2PR2 |= ((1 << 17) | (1 << 19));
    // All bits except 18, 20, 21, and 22 in PR3 are reserved and the original
    // value must be preserved
    EXTI->C2PR3 |= ((1 << 18) | (1 << 20) | (1 << 21) | (1 << 22));
    // <--

    // Disable and clear all pending interrupts in the NVIC. There are 8
    // registers in the Cortex-M4.
    for (auto i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xffffffff;
        NVIC->ICPR[i] = 0xffffffff;
    }

    HAL_PWREx_EnterSTANDBYMode(PWR_D3_DOMAIN);

    HAL_PWREx_EnterSTANDBYMode(PWR_D2_DOMAIN);

    return LowPowerReturnCode::m4StandbyFailed;
}

uint64_t LowPowerPortentaH7::timeSinceBoot() const
{
    mbed_stats_cpu_t stats{};
    mbed_stats_cpu_get(&stats);
    return stats.uptime;
}

uint64_t LowPowerPortentaH7::timeSpentIdle() const
{
    mbed_stats_cpu_t stats{};
    mbed_stats_cpu_get(&stats);
    return stats.idle_time;
}

uint64_t LowPowerPortentaH7::timeSpentInDeepSleep() const
{
    mbed_stats_cpu_t stats{};
    mbed_stats_cpu_get(&stats);
    return stats.deep_sleep_time;
}

uint64_t LowPowerPortentaH7::timeSpentInSleep() const
{
    mbed_stats_cpu_t stats{};
    mbed_stats_cpu_get(&stats);
    return stats.sleep_time;
}

bool LowPowerPortentaH7::turnOffEthernet() const
{
    uint8_t dummyMAC[6]{};
    ETH_DMADescTypeDef dummyTX[ETH_TX_DESC_CNT]{};
    ETH_DMADescTypeDef dummyRX[ETH_RX_DESC_CNT]{};

    ethHandle.Instance = ETH;
    ethHandle.Init.MACAddr = dummyMAC;
    ethHandle.Init.MediaInterface = HAL_ETH_RMII_MODE;
    ethHandle.Init.RxDesc = dummyRX;
    ethHandle.Init.TxDesc = dummyTX;
    ethHandle.Init.RxBuffLen = 0U;

    if (HAL_OK != HAL_ETH_Init(&ethHandle))
    {
        return false;
    }
    if (LAN8742_STATUS_OK != LAN8742_RegisterBusIO(&LAN8742, &LAN8742_IOCtx))
    {
        return false;
    }
    if (LAN8742_STATUS_OK != LAN8742_Init(&LAN8742))
    {
        return false;
    }
    if (LAN8742_STATUS_OK != LAN8742_EnablePowerDownMode(&LAN8742))
    {
        return false;
    }
    return true;
}

void LowPowerPortentaH7::waitForFlashReady() const
{
    // Make sure the flash controller isn't busy before we continue, since
    // that would block standby mode.
    //
    // 0x07 = QW, WBNE, and BSY flags
    while ((FLASH->SR1 & 0x07) || (FLASH->SR2 & 0x07))
      ;
}

bool LowPowerPortentaH7::wasInCPUMode(CPUMode mode) const
{
    const auto registerValue = PWR->CPUCR;

    switch (mode)
    {
        case CPUMode::d1DomainStandby:
            return registerValue & PWR_CPUCR_SBF_D1;
        case CPUMode::d2DomainStandby:
            return registerValue & PWR_CPUCR_SBF_D2;
        case CPUMode::standby:
            return registerValue & PWR_CPUCR_SBF;
        case CPUMode::stop:
            return registerValue & PWR_CPUCR_STOPF;
        default:
            return false;
    }

    return false;
}
