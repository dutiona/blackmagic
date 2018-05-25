#include <blackmagic/integral/integral.hpp>

#include <iostream>

#include <gtest/gtest.h>

namespace integral = blackmagic::integral;

using namespace integral::literals;

// arithmetic

TEST(Integral_Operators, Arithmetic_Positive)
{
  static_assert((+1_c) == 1_c);
  static_assert((+1_c) == 1_c);
}

TEST(Integral_Operators, Arithmetic_Negative)
{
  static_assert((-1_c) == (-1_c));
}

TEST(Integral_Operators, Arithmetic_Plus)
{
  static_assert((1_c + 1_c) == 2_c);
  static_assert((1_c + (-1_c)) == 0_c);
}

TEST(Integral_Operators, Arithmetic_Minus)
{
  static_assert((1_c - 1_c) == 0_c);
  static_assert((1_c - (-1_c)) == 2_c);
}

TEST(Integral_Operators, Arithmetic_Div)
{
  static_assert((10_c / 2_c) == 5_c);
}

TEST(Integral_Operators, Arithmetic_Mult)
{
  static_assert((10_c * 2_c) == 20_c);
}

TEST(Integral_Operators, Arithmetic_Mod)
{
  static_assert((10_c % 3_c) == 1_c);
}

TEST(Integral_Operators, Arithmetic_BitNot)
{
  static_assert((~0b1_c & 0b1111_c) == 0b1110_c);
}

TEST(Integral_Operators, Arithmetic_BitAnd)
{
  static_assert((0b0101_c & 0b0110_c) == 0b0100_c);
}

TEST(Integral_Operators, Arithmetic_BitOr)
{
  static_assert((0b0101_c | 0b1110_c) == 0b1111_c);
}

TEST(Integral_Operators, Arithmetic_BitXor)
{
  static_assert((0b0101_c ^ 0b1110_c) == 0b1011_c);
}

TEST(Integral_Operators, Arithmetic_BitLshift)
{
  static_assert((0b0001_c << 2_c) == 0b0100_c);
}

TEST(Integral_Operators, Arithmetic_BitRshift)
{
  static_assert((0b0100_c >> 2_c) == 0b0001_c);
}


// comparison

TEST(Integral_Operators, Comparison_EqualTo)
{
  static_assert(1_c == 1_c);
  static_assert("true"_bc == "true"_bc);
  static_assert("false"_bc == "false"_bc);
}

TEST(Integral_Operators, Comparison_NotEqualTo)
{
  static_assert(1_c != 2_c);
  static_assert("false"_bc != "true"_bc);
}

TEST(Integral_Operators, Comparison_LessThan)
{
  static_assert(1_c < 2_c);
  static_assert(!(1_c < 1_c));
}

TEST(Integral_Operators, Comparison_LessEqualThan)
{
  static_assert(1_c <= 2_c);
  static_assert(1_c <= 1_c);
}

TEST(Integral_Operators, Comparison_GreaterThan)
{
  static_assert(2_c > 1_c);
  static_assert(!(1_c > 1_c));
}

TEST(Integral_Operators, Comparison_GreaterEqualThan)
{
  static_assert(2_c >= 1_c);
  static_assert(1_c >= 1_c);
}


// logical

TEST(Integral_Operators, Logical_Not)
{
  static_assert((!"false"_bc) == "true"_bc);
  static_assert((!"false"_bc) != "false"_bc);
  static_assert((!"true"_bc) == "false"_bc);
  static_assert((!"true"_bc) != "true"_bc);
}

TEST(Integral_Operators, Logical_And)
{
  static_assert(("true"_bc && "false"_bc) == "false"_bc);
  static_assert(("false"_bc && "true"_bc) == "false"_bc);
  static_assert(("true"_bc && "true"_bc) == "true"_bc);
  static_assert(("false"_bc && "false"_bc) == "false"_bc);
}

TEST(Integral_Operators, Logical_Or)
{
  static_assert(("true"_bc || "false"_bc) == "true"_bc);
  static_assert(("false"_bc || "true"_bc) == "true"_bc);
  static_assert(("true"_bc || "true"_bc) == "true"_bc);
  static_assert(("false"_bc || "false"_bc) == "false"_bc);
}
