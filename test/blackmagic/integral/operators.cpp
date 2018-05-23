#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace integral = blackmagic::integral;

using namespace integral::literals;

// arithmetic

TEST(Integral_Operators, Arithmetic_Increment)
{
}

TEST(Integral_Operators, Arithmetic_Decrement)
{
}

TEST(Integral_Operators, Arithmetic_Positive)
{
}

TEST(Integral_Operators, Arithmetic_Negative)
{
}

TEST(Integral_Operators, Arithmetic_Plus)
{
}

TEST(Integral_Operators, Arithmetic_Minus)
{
}

TEST(Integral_Operators, Arithmetic_Div)
{
}

TEST(Integral_Operators, Arithmetic_Mult)
{
}

TEST(Integral_Operators, Arithmetic_Mod)
{
}

TEST(Integral_Operators, Arithmetic_BitNot)
{
}

TEST(Integral_Operators, Arithmetic_BitAnd)
{
}

TEST(Integral_Operators, Arithmetic_BitOr)
{
}

TEST(Integral_Operators, Arithmetic_BitXor)
{
}

TEST(Integral_Operators, Arithmetic_BitLshift)
{
}

TEST(Integral_Operators, Arithmetic_BitRshift)
{
}


// comparison

TEST(Integral_Operators, Comparison_EqualTo)
{
}

TEST(Integral_Operators, Comparison_NotEqualTo)
{
}

TEST(Integral_Operators, Comparison_LessThan)
{
}

TEST(Integral_Operators, Comparison_LessEqualThan)
{
}

TEST(Integral_Operators, Comparison_GreaterThan)
{
}

TEST(Integral_Operators, Comparison_GreaterEqualThan)
{
}


// logical

TEST(Integral_Operators, Logical_EqualTo)
{
  static_assert(1_c == 1_c);
  static_assert("true"_bc == "true"_bc);
  static_assert("false"_bc == "false"_bc);
}

TEST(Integral_Operators, Logical_NotEqualTo)
{
  static_assert(1_c != 2_c);
  static_assert("false"_bc != "true"_bc);
}

TEST(Integral_Operators, Logical_Not)
{
  static_assert(!"false"_bc == "true"_bc);
  static_assert(!"false"_bc != "false"_bc);
  static_assert(!"true"_bc == "false"_bc);
  static_assert(!"true"_bc != "true"_bc);
}
