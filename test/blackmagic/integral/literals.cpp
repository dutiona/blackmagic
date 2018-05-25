#include <blackmagic/integral/integral.hpp>

#include <type_traits>

#include <gtest/gtest.h>

namespace integral = blackmagic::integral;

using namespace integral::literals;

// _c long long
TEST(Integral_Literals, Common)
{
  static_assert(std::is_same_v<integral::long_long_t<1>, std::remove_reference_t<decltype(1_c)>>);
  static_assert(std::is_same_v<integral::long_long_t<1>::value_type, long long>);
  static_assert(integral::long_long_v<1> == 1);
}

// _bc bool
TEST(Integral_Literals, Bool)
{
  static_assert(std::is_same_v<integral::bool_t<true>, std::remove_reference_t<decltype("true"_bc)>>);
  static_assert(std::is_same_v<integral::bool_t<true>::value_type, bool>);
  static_assert(integral::bool_v<true> == true);

  static_assert(std::is_same_v<integral::bool_t<false>, std::remove_reference_t<decltype("false"_bc)>>);
  static_assert(std::is_same_v<integral::bool_t<false>::value_type, bool>);
  static_assert(integral::bool_v<false> == false);

  static_assert(std::is_same_v<integral::bool_t<true>, integral::true_t>);
  static_assert(integral::true_v == true);

  static_assert(std::is_same_v<integral::bool_t<false>, integral::false_t>);
  static_assert(integral::false_v == false);
}

// _cc char
TEST(Integral_Literals, Char)
{
  static_assert(std::is_same_v<integral::char_t<'a'>, std::remove_reference_t<decltype("a"_cc)>>);
  static_assert(std::is_same_v<integral::char_t<'a'>::value_type, char>);
  static_assert(integral::char_v<'a'> == 'a');
}

// _sc short
TEST(Integral_Literals, Short)
{
  constexpr short a = 1;
  static_assert(std::is_same_v<integral::short_t<a>, std::remove_reference_t<decltype(1_sc)>>);
  static_assert(std::is_same_v<integral::short_t<a>::value_type, short>);
  static_assert(integral::short_v<a> == 1);
}

// _ic int
TEST(Integral_Literals, Int)
{
  static_assert(std::is_same_v<integral::int_t<1>, std::remove_reference_t<decltype(1_ic)>>);
  static_assert(std::is_same_v<integral::int_t<1>::value_type, int>);
  static_assert(integral::int_v<1> == 1);
}

// _lc long
TEST(Integral_Literals, Long)
{
  static_assert(std::is_same_v<integral::long_t<1>, std::remove_reference_t<decltype(1_lc)>>);
  static_assert(std::is_same_v<integral::long_t<1>::value_type, long>);
  static_assert(integral::long_v<1> == 1);
}

// _llc long long
TEST(Integral_Literals, LongLong)
{
  static_assert(std::is_same_v<integral::long_long_t<1>, std::remove_reference_t<decltype(1_llc)>>);
  static_assert(std::is_same_v<integral::long_long_t<1>::value_type, long long>);
  static_assert(integral::long_long_v<1> == 1);
}

// _ucc unsigned char
TEST(Integral_Literals, UnsignedChar)
{
  static_assert(std::is_same_v<integral::unsigned_char_t<'a'>, std::remove_reference_t<decltype("a"_ucc)>>);
  static_assert(std::is_same_v<integral::unsigned_char_t<'a'>::value_type, unsigned char>);
  static_assert(integral::unsigned_char_v<'a'> == 'a');
}

// _usc unsigned short
TEST(Integral_Literals, UnsignedShort)
{
  constexpr unsigned short a = 1;
  static_assert(std::is_same_v<integral::unsigned_short_t<a>, std::remove_reference_t<decltype(1_usc)>>);
  static_assert(std::is_same_v<integral::unsigned_short_t<a>::value_type, unsigned short>);
  static_assert(integral::unsigned_short_v<a> == 1);
}

// _uc unsigned common
TEST(Integral_Literals, Unsigned)
{
  static_assert(std::is_same_v<integral::unsigned_t<1>, std::remove_reference_t<decltype(1_uc)>>);
  static_assert(std::is_same_v<integral::unsigned_t<1>::value_type, unsigned>);
  static_assert(integral::unsigned_v<1> == 1);
}

// _uic unsigned int
TEST(Integral_Literals, UnsignedInt)
{
  static_assert(std::is_same_v<integral::unsigned_int_t<1>, std::remove_reference_t<decltype(1_uic)>>);
  static_assert(std::is_same_v<integral::unsigned_int_t<1>::value_type, unsigned int>);
  static_assert(integral::unsigned_int_v<1> == 1);
}

// _ulc unsigned long
TEST(Integral_Literals, UnsignedLong)
{
  static_assert(std::is_same_v<integral::unsigned_long_t<1>, std::remove_reference_t<decltype(1_ulc)>>);
  static_assert(std::is_same_v<integral::unsigned_long_t<1>::value_type, unsigned long>);
  static_assert(integral::unsigned_long_v<1> == 1);
}

// _ullc unsigned long long
TEST(Integral_Literals, UnsignedLongLong)
{
  static_assert(std::is_same_v<integral::unsigned_long_long_t<1>, std::remove_reference_t<decltype(1_ullc)>>);
  static_assert(std::is_same_v<integral::unsigned_long_long_t<1>::value_type, unsigned long long>);
  static_assert(integral::unsigned_long_long_v<1> == 1);
}

// _stc size_t
TEST(Integral_Literals, Size_t)
{
  static_assert(std::is_same_v<integral::size_t_t <1>, std::remove_reference_t<decltype(1_stc)>>);
  static_assert(std::is_same_v<integral::size_t_t<1>::value_type, size_t>);
  static_assert(integral::size_t_v<1> == 1);
}

