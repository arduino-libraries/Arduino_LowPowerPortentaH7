/*
********************************************************************************
*
* The templates in the library are ok if this sketch compiles, but if not, the
* static asserts will state what is wrong. There is no need to actually upload
* and run the sketch. All checks are made at compile time.
*
* Original author: A. Vidstrom (http://arduino.cc)
*
* This code is in the public domain
*
********************************************************************************
*/

#include "Arduino_LowPowerPortentaH7.h"

// Test #1 -->

template <typename T> constexpr bool test1(...)
{
    return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test1(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed, 15_s))* dummy) {
    return true;
} 

// <-- Test 1

// Test #2 -->

template <typename T> constexpr bool test2(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test2(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilTimeElapsed, 15_s))* dummy)
{
    return true;
}

// <-- Test 2

// Test #3 -->

template <typename T> constexpr bool test3(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test3(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilPinActivity))* dummy)
{
    return true;
}

// <-- Test 3

// Test #4 -->

template <typename T> constexpr bool test4(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test4(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed))* dummy)
{
    return true;
}

// <-- Test 4

// Test #5 -->

template <typename T> constexpr bool test5(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test5(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilTimeElapsed | LowPowerStandbyType::untilPinActivity))* dummy)
{
    return true;
}

// <-- Test 5

// Test #6 -->

template <typename T> constexpr bool test6(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test6(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilTimeElapsed))* dummy)
{
    return true;
}

// <-- Test 6

// Test #7 -->

template <typename T> constexpr bool test7(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test7(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilPinActivity, 15_s))* dummy)
{
    return true;
}

// <-- Test 7

// Test #8 -->

template <typename T> constexpr bool test8(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test8(decltype(std::declval<T>().standbyM7())* dummy)
{
    return true;
}

// <-- Test 8

// Test #9 -->

template <typename T> constexpr bool test9(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test9(decltype(std::declval<T>().standbyM7(LowPowerStandbyType::untilTimeElapsed, 15_s, 1234))* dummy)
{
    return true;
}

// <-- Test 9

// Test #10 -->

template <typename T> constexpr bool test10(...)
{
  return false;
}

// T has a private constructor, hence declval
template <typename T>
constexpr bool test10(decltype(std::declval<T>().standbyM7(1234))* dummy)
{
    return true;
}

// <-- Test 10

void setup() {
  // Notice that nullptr and * are necessary to make the true-returning variety more specific. It takes a pointer
  // and so we must pass a pointer. Removing these two makes the compiling versions return false.

  // The valid ways to call standbyM7()
  static_assert(test1<decltype(LowPower)>(nullptr), "The function call in Test #1 should compile but failed to do so");
  static_assert(test2<decltype(LowPower)>(nullptr), "The function call in Test #2 should compile but failed to do so");
  static_assert(test3<decltype(LowPower)>(nullptr), "The function call in Test #3 should compile but failed to do so");
  
  // The invalid ways to call standbyM7()
  static_assert(!test4<decltype(LowPower)>(nullptr), "The function call in Test #4 should not compile but did so anyway");
  static_assert(!test5<decltype(LowPower)>(nullptr), "The function call in Test #5 should not compile but did so anyway");
  static_assert(!test6<decltype(LowPower)>(nullptr), "The function call in Test #6 should not compile but did so anyway");
  static_assert(!test7<decltype(LowPower)>(nullptr), "The function call in Test #7 should not compile but did so anyway");
  static_assert(!test8<decltype(LowPower)>(nullptr), "The function call in Test #8 should not compile but did so anyway");
  static_assert(!test9<decltype(LowPower)>(nullptr), "The function call in Test #9 should not compile but did so anyway");
  static_assert(!test10<decltype(LowPower)>(nullptr), "The function call in Test #10 should not compile but did so anyway");
}

void loop(){
}
