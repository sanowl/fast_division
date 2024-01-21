#include "fast_division/fast_division.h"
#include <iostream>
#include <iomanip> // Added for setw

// Helper function to print large integers
std::ostream &operator<<(std::ostream &dest, __uint128_t value)
{
  std::ostream::sentry s(dest);
  if (s)
  {
    __uint128_t tmp = value;
    char buffer[128];
    char *d = std::end(buffer);
    do
    {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    int len = int(std::end(buffer) - d);
    if (dest.rdbuf()->sputn(d, len) != len)
    {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

template <uint32_t Divisor>
void test32()
{
  std::cout << "(32-bit) Testing " << Divisor << std::endl;
  for (uint32_t n = 1; n != 0; n++)
  {
    bool quotient_ok = fast_division::Divide32<Divisor>::CalculateQuotient(n) == n / Divisor;
    bool remainder_ok = fast_division::Divide32<Divisor>::CalculateRemainder(n) == n % Divisor;
    bool divisible_ok = fast_division::Divide32<Divisor>::IsDivisible(n) == (n % Divisor == 0);

    if (!quotient_ok || !remainder_ok || !divisible_ok)
    {
      std::cerr << "Problem with n = " << n << std::endl;
      std::cout << "Quotient: " << fast_division::Divide32<Divisor>::CalculateQuotient(n)
                << " Expected: " << n / Divisor << std::endl;
      std::cout << "Remainder: " << fast_division::Divide32<Divisor>::CalculateRemainder(n)
                << " Expected: " << n % Divisor << std::endl;
      std::cout << "Divisible: " << fast_division::Divide32<Divisor>::IsDivisible(n)
                << " Expected: " << (n % Divisor == 0) << std::endl;

      // Print additional information for debugging
      std::cout << std::setw(15) << "Need fallback: " << fast_division::Divide32<Divisor>::NeedFallback << std::endl;
      std::cout << std::setw(15) << "Is power of 2: " << fast_division::Divide32<Divisor>::IsPowerOf2 << std::endl;
      std::cout << std::setw(15) << "C: " << fast_division::Divide32<Divisor>::C << std::endl;
      std::cout << std::setw(15) << "Leading zeroes: " << fast_division::Divide32<Divisor>::LeadingZeroes << std::endl;
      std::cout << std::setw(15) << "Log2 divisor: " << fast_division::Divide32<Divisor>::Log2Divisor << std::endl;
      std::cout << std::setw(15) << "M: " << fast_division::Divide32<Divisor>::M << std::endl;
      std::cout << std::setw(15) << "Overflow: " << fast_division::Divide32<Divisor>::Overflow << std::endl;

      abort();
    }
  }
}

template <uint64_t Divisor>
void test64()
{
  std::cout << "(64-bit) Testing " << Divisor << std::endl;
  for (uint64_t n = 1; n != 0; n++)
  {
    if (n == 1000000)
    {
      n = 0xFFFFFFFFFFFFFFFF - 1000000;
    }
    bool quotient_ok = fast_division::Divide64<Divisor>::CalculateQuotient(n) == n / Divisor;
    bool remainder_ok = fast_division::Divide64<Divisor>::CalculateRemainder(n) == n % Divisor;
    bool divisible_ok = fast_division::Divide64<Divisor>::IsDivisible(n) == (n % Divisor == 0);

    if (!quotient_ok || !remainder_ok || !divisible_ok)
    {
      std::cerr << "Problem with n = " << n << std::endl;
      std::cout << "Quotient: " << fast_division::Divide64<Divisor>::CalculateQuotient(n)
                << " Expected: " << n / Divisor << std::endl;
      std::cout << "Remainder: " << fast_division::Divide64<Divisor>::CalculateRemainder(n)
                << " Expected: " << n % Divisor << std::endl;
      std::cout << "Divisible: " << fast_division::Divide64<Divisor>::IsDivisible(n)
                << " Expected: " << (n % Divisor == 0) << std::endl;

      // Print additional information for debugging
      std::cout << std::setw(15) << "Need fallback: " << fast_division::Divide64<Divisor>::NeedFallback << std::endl;
      std::cout << std::setw(15) << "Is power of 2: " << fast_division::Divide64<Divisor>::IsPowerOf2 << std::endl;
      std::cout << std::setw(15) << "C: " << fast_division::Divide64<Divisor>::C << std::endl;
      std::cout << std::setw(15) << "Leading zeroes: " << fast_division::Divide64<Divisor>::LeadingZeroes << std::endl;
      std::cout << std::setw(15) << "Log2 divisor: " << fast_division::Divide64<Divisor>::Log2Divisor << std::endl;
      std::cout << std::setw(15) << "M: " << fast_division::Divide64<Divisor>::M << std::endl;
      std::cout << std::setw(15) << "Overflow: " << fast_division::Divide64<Divisor>::Overflow << std::endl;

      abort();
    }
  }
}

int main()
{
  // Testing for various divisors
  test64<1000000001>();
  test64<1232445>();
  test64<67910>();
  test64<8>();
  test64<19>();
  test64<461>();

  test32<1000000001>();
  test32<1232445>();
  test32<67910>();
  test32<8>();
  test32<19>();
  test32<461>();

  std::cout << "All tests passed successfully!" << std::endl;

  return 0;
}
