#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace integral = blackmagic::integral;

using namespace integral::literals;

TEST(Integral_Operators, Logical_EqualTo)
{
  static_assert(1_c == 1_c);
  static_assert(0_bc == 0_bc);
}

TEST(Integral_Operators, Logical_NotEqualTo)
{
  static_assert(1_c != 2_c);
  static_assert(0_bc != 1_bc);
}

TEST(Integral_Operators, Logical_Not)
{
  static_assert(!0_bc == 1_bc);
  static_assert(!0_bc != 0_bc);
  static_assert(!1_bc == 0_bc);
  static_assert(!1_bc != 1_bc);
}
