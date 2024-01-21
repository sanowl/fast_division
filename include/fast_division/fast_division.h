#ifndef FAST_DIVISION_H
#define FAST_DIVISION_H

#include <cstdint>

namespace fast_division
{

  // Structure for fast division of 32-bit unsigned integers
  template <uint32_t Divisor>
  struct Divide32
  {
    constexpr static int LeadingZeroes = __builtin_clz(Divisor);
    constexpr static int Log2Divisor = 31 - LeadingZeroes;
    constexpr static bool IsPowerOf2 = ((Divisor & (Divisor - 1)) == 0);
    constexpr static uint32_t PowerOf2Mask = ~uint32_t(int32_t(0x80000000) >> LeadingZeroes);

    // Calculate quotient
    static inline uint32_t Quotient(uint32_t n) noexcept
    {
      return IsPowerOf2 ? n >> Log2Divisor : n / Divisor;
    }

    // Calculate remainder
    static inline uint32_t Remainder(uint32_t n) noexcept
    {
      return IsPowerOf2 ? n & PowerOf2Mask : n % Divisor;
    }

    // Check if divisible
    static inline bool IsDivisible(uint32_t n) noexcept
    {
      return IsPowerOf2 ? (n & PowerOf2Mask) == 0 : n % Divisor == 0;
    }
  };

  // Structure for fast division of 64-bit unsigned integers
  template <uint64_t Divisor>
  struct Divide64
  {
    constexpr static int LeadingZeroes = __builtin_clzll(Divisor);
    constexpr static int Log2Divisor = 63 - LeadingZeroes;
    constexpr static bool IsPowerOf2 = ((Divisor & (Divisor - 1)) == 0);
    constexpr static uint64_t PowerOf2Mask = ~uint64_t(int64_t(0x8000000000000000) >> LeadingZeroes);

    // Calculate quotient
    static inline uint64_t Quotient(uint64_t n) noexcept
    {
      return IsPowerOf2 ? n >> Log2Divisor : n / Divisor;
    }

    // Calculate remainder
    static inline uint64_t Remainder(uint64_t n) noexcept
    {
      return IsPowerOf2 ? n & PowerOf2Mask : n % Divisor;
    }

    // Check if divisible
    static inline bool IsDivisible(uint64_t n) noexcept
    {
      return IsPowerOf2 ? (n & PowerOf2Mask) == 0 : n % Divisor == 0;
    }
  };

} // namespace fast_division

#endif
