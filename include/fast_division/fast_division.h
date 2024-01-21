#ifndef FAST_DIVISION_H
#define FAST_DIVISION_H

#include <cstdint>

namespace fast_division
{

  // Structure for fast division of 32-bit unsigned integers
  template <uint32_t Divisor>
  struct Divide32
  {
    static constexpr int LeadingZeroes = __builtin_clz(Divisor);
    static constexpr int Log2Divisor = 31 - LeadingZeroes;
    static constexpr bool IsPowerOf2 = (Divisor & (Divisor - 1)) == 0;
    static constexpr uint32_t PowerOf2Mask = ~uint32_t(int32_t(0x80000000) >> LeadingZeroes);

    // Calculate quotient
    static inline uint32_t CalculateQuotient(uint32_t numerator) noexcept
    {
      return IsPowerOf2 ? numerator >> Log2Divisor : numerator / Divisor;
    }

    // Calculate remainder
    static inline uint32_t CalculateRemainder(uint32_t numerator) noexcept
    {
      return IsPowerOf2 ? numerator & PowerOf2Mask : numerator % Divisor;
    }

    // Check if divisible
    static inline bool IsDivisible(uint32_t numerator) noexcept
    {
      return IsPowerOf2 ? (numerator & PowerOf2Mask) == 0 : numerator % Divisor == 0;
    }
  };

  // Structure for fast division of 64-bit unsigned integers
  template <uint64_t Divisor>
  struct Divide64
  {
    static constexpr int LeadingZeroes = __builtin_clzll(Divisor);
    static constexpr int Log2Divisor = 63 - LeadingZeroes;
    static constexpr bool IsPowerOf2 = (Divisor & (Divisor - 1)) == 0;
    static constexpr uint64_t PowerOf2Mask = ~uint64_t(int64_t(0x8000000000000000) >> LeadingZeroes);

    // Calculate quotient
    static inline uint64_t CalculateQuotient(uint64_t numerator) noexcept
    {
      return IsPowerOf2 ? numerator >> Log2Divisor : numerator / Divisor;
    }

    // Calculate remainder
    static inline uint64_t CalculateRemainder(uint64_t numerator) noexcept
    {
      return IsPowerOf2 ? numerator & PowerOf2Mask : numerator % Divisor;
    }

    // Check if divisible
    static inline bool IsDivisible(uint64_t numerator) noexcept
    {
      return IsPowerOf2 ? (numerator & PowerOf2Mask) == 0 : numerator % Divisor == 0;
    }
  };

} // namespace fast_division

#endif
