#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace integral = blackmagic::integral;

using namespace integral::literals;

TEST(Integral_Traits, Bool)
{
  static_assert(integral::is_bool_c_v<integral::bool_t<true>>);
}

TEST(Integral_Traits, Char)
{
  static_assert(integral::is_char_c_v<integral::char_t<'a'>>);
}

TEST(Integral_Traits, Short)
{
  static_assert(integral::is_short_c_v<integral::short_t<1>>);
}

TEST(Integral_Traits, Int)
{
  static_assert(integral::is_int_c_v<integral::int_t<1>>);
}

TEST(Integral_Traits, Long)
{
  static_assert(integral::is_long_c_v<integral::long_t<1>>);
}

TEST(Integral_Traits, LongLong)
{
  static_assert(integral::is_long_long_c_v<integral::long_long_t<1>>);
}

TEST(Integral_Traits, UnsignedChar)
{
  static_assert(integral::is_unsigned_char_c_v<integral::unsigned_char_t<'a'>>);
}

TEST(Integral_Traits, UnsignedShort)
{
  static_assert(integral::is_unsigned_short_c_v<integral::unsigned_short_t<1>>);
}

TEST(Integral_Traits, Unsigned)
{
  static_assert(integral::is_unsigned_c_v<integral::unsigned_t<1>>);
}

TEST(Integral_Traits, UnsignedInt)
{
  static_assert(integral::is_unsigned_int_c_v<integral::unsigned_int_t<1>>);
}

TEST(Integral_Traits, UnsignedLong)
{
  static_assert(integral::is_unsigned_long_c_v<integral::unsigned_long_t<1>>);
}

TEST(Integral_Traits, UnsignedLongLong)
{
  static_assert(integral::is_unsigned_long_long_c_v<integral::unsigned_long_long_t<1>>);
}

TEST(Integral_Traits, Size_t)
{
  static_assert(integral::is_size_t_c_v<integral::size_t_t<1>>);
}
