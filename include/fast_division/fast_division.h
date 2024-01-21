#ifndef FAST_DIVISION_H
#define FAST_DIVISION_H

#include <cstdint>

namespace fast_division
{

  template <uint32_t divisor>
  struct divide32
  {
    constexpr static int leading_zeroes = __builtin_clz(divisor);
    constexpr static int log2_divisor = 31 - leading_zeroes;
    constexpr static bool is_power_2 = ((divisor & (divisor - 1)) == 0);
    constexpr static uint32_t power_2_mask = ~uint32_t(int32_t(0x80000000) >> leading_zeroes);

    static inline uint32_t quotient(uint32_t n) noexcept
    {
      return is_power_2 ? n >> log2_divisor : n / divisor;
    }

    static inline uint32_t remainder(uint32_t n) noexcept
    {
      return is_power_2 ? n & power_2_mask : n % divisor;
    }

    static inline bool is_divisible(uint32_t n) noexcept
    {
      return is_power_2 ? (n & power_2_mask) == 0 : n % divisor == 0;
    }
  };

  template <uint64_t divisor>
  struct divide64
  {
    constexpr static int leading_zeroes = __builtin_clzll(divisor);
    constexpr static int log2_divisor = 63 - leading_zeroes;
    constexpr static bool is_power_2 = ((divisor & (divisor - 1)) == 0);
    constexpr static uint64_t power_2_mask = ~uint64_t(int64_t(0x8000000000000000) >> leading_zeroes);

    static inline uint64_t quotient(uint64_t n) noexcept
    {
      return is_power_2 ? n >> log2_divisor : n / divisor;
    }

    static inline uint64_t remainder(uint64_t n) noexcept
    {
      return is_power_2 ? n & power_2_mask : n % divisor;
    }

    static inline bool is_divisible(uint64_t n) noexcept
    {
      return is_power_2 ? (n & power_2_mask) == 0 : n % divisor == 0;
    }
  };

} // namespace fast_division

#endif
