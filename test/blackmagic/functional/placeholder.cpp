#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
using namespace functional::placeholder;

TEST(Functional_Placeholder, Assignement)
{
  int a = 0;
  ASSERT_TRUE(&a == &(_ = _)(a, 5));
  ASSERT_TRUE(a == 5);

  a = 0;
  ASSERT_TRUE(&a == &(_ = 5)(a));
  ASSERT_TRUE(a == 5);
}


TEST(Functional_Placeholder, Subscript)
{
  int a[] = {1, 2, 3};
  ASSERT_TRUE(&a[2] == &(_[_])(a, 2));
  ASSERT_TRUE(a[2] == (_[_])(a, 2));

  ASSERT_TRUE(&a[2] == &(_[2])(a));
  ASSERT_TRUE(a[2] == (_[2])(a));
}


TEST(Functional_Placeholder, Invocable)
{
  ASSERT_TRUE(6 == (_(1, 2, 3))([](auto a, auto b, auto c) { return a + b + c; }));
}


TEST(Functional_Placeholder, MemberAccess)
{
  int a = 1;
  ASSERT_TRUE(&a == (&_)(a));

  int* ptr = &a;
  ASSERT_TRUE(*ptr == (*_)(ptr));
}


TEST(Functional_Placeholder, Arithmetic_Increment)
{
  int a = 0;
  ASSERT_TRUE(0 == (_++)(a));
  ASSERT_TRUE(a == 1);

  a = 0;
  ASSERT_TRUE(1 == (++_)(a));

  a = 0;
  ASSERT_TRUE(&a == &(++_)(a));
  ASSERT_TRUE(a == 1);
}

TEST(Functional_Placeholder, Arithmetic_Decrement)
{
  int a = 0;
  ASSERT_TRUE(0 == (_--)(a));
  ASSERT_TRUE(a == -1);

  a = 0;
  ASSERT_TRUE(-1 == (--_)(a));

  a = 0;
  ASSERT_TRUE(&a == &(--_)(a));
  ASSERT_TRUE(a == -1);
}

TEST(Functional_Placeholder, Arithmetic_BinaryPLus)
{
  ASSERT_TRUE(4 + 5 == (_ + _)(4, 5));
  ASSERT_TRUE(4 + 5 == (4 + _)(5));
  ASSERT_TRUE(4 + 5 == (_ + 5)(4));
}

TEST(Functional_Placeholder, Arithmetic_BinaryMinus)
{
  ASSERT_TRUE(4 - 5 == (_ - _)(4, 5));
  ASSERT_TRUE(4 - 5 == (4 - _)(5));
  ASSERT_TRUE(4 - 5 == (_ - 5)(4));
}

TEST(Functional_Placeholder, Arithmetic_Mult)
{
  ASSERT_TRUE(4 * 5 == (_ * _)(4, 5));
  ASSERT_TRUE(4 * 5 == (4 * _)(5));
  ASSERT_TRUE(4 * 5 == (_ * 5)(4));
}

TEST(Functional_Placeholder, Arithmetic_Div)
{
  ASSERT_TRUE(4 / 5 == (_ / _)(4, 5));
  ASSERT_TRUE(4 / 5 == (4 / _)(5));
  ASSERT_TRUE(4 / 5 == (_ / 5)(4));
}

TEST(Functional_Placeholder, Arithmetic_Mod)
{
  ASSERT_TRUE(4 % 5 == (_ % _)(4, 5));
  ASSERT_TRUE(4 % 5 == (4 % _)(5));
  ASSERT_TRUE(4 % 5 == (_ % 5)(4));
}

TEST(Functional_Placeholder, Arithmetic_UnaryPlus)
{
  ASSERT_TRUE(+4 == (+_)(4));
}

TEST(Functional_Placeholder, Arithmetic_UnaryMinus)
{
  ASSERT_TRUE(-4 == (-_)(4));
}

TEST(Functional_Placeholder, Arithmetic_Assignement_Plus)
{
  int a = 0;
  ASSERT_TRUE(&a == &(_ += _)(a, 5));
  ASSERT_TRUE(a == 5);

  a = 0;
  ASSERT_TRUE(&a == &(a += _)(5));
  ASSERT_TRUE(a == 5);

  a = 0;
  ASSERT_TRUE(&a == &(_ += 5)(a));
  ASSERT_TRUE(a == 5);
}

TEST(Functional_Placeholder, Arithmetic_Assignement_Minus)
{
  int a = 0;
  ASSERT_TRUE(&a == &(_ -= _)(a, 5));
  ASSERT_TRUE(a == -5);

  a = 0;
  ASSERT_TRUE(&a == &(a -= _)(5));
  ASSERT_TRUE(a == -5);

  a = 0;
  ASSERT_TRUE(&a == &(_ -= 5)(a));
  ASSERT_TRUE(a == -5);
}

TEST(Functional_Placeholder, Arithmetic_Assignement_Mult)
{
  int a = 1;
  ASSERT_TRUE(&a == &(_ *= _)(a, 5));
  ASSERT_TRUE(a == 5);

  a = 1;
  ASSERT_TRUE(&a == &(a *= _)(5));
  ASSERT_TRUE(a == 5);

  a = 1;
  ASSERT_TRUE(&a == &(_ *= 5)(a));
  ASSERT_TRUE(a == 5);
}

TEST(Functional_Placeholder, Arithmetic_Assignement_Div)
{
  int a = 10;
  ASSERT_TRUE(&a == &(_ /= _)(a, 5));
  ASSERT_TRUE(a == 2);

  a = 10;
  ASSERT_TRUE(&a == &(a /= _)(5));
  ASSERT_TRUE(a == 2);

  a = 10;
  ASSERT_TRUE(&a == &(_ /= 5)(a));
  ASSERT_TRUE(a == 2);
}

TEST(Functional_Placeholder, Arithmetic_Assignement_Mod)
{
  int a = 10;
  ASSERT_TRUE(&a == &(_ %= _)(a, 5));
  ASSERT_TRUE(a == 0);

  a = 10;
  ASSERT_TRUE(&a == &(a %= _)(5));
  ASSERT_TRUE(a == 0);

  a = 10;
  ASSERT_TRUE(&a == &(_ %= 5)(a));
  ASSERT_TRUE(a == 0);
}


TEST(Functional_Placeholder, Bitwise_Not)
{
  ASSERT_TRUE(~0b1 == (~_)(0b1));
}

TEST(Functional_Placeholder, Bitwise_And)
{
  ASSERT_TRUE((0b0111 & 0b1010) == (_ & _)(0b0111, 0b1010));
  ASSERT_TRUE((0b0111 & 0b1010) == (0b0111 & _)(0b1010));
  ASSERT_TRUE((0b0111 & 0b1010) == (_ & 0b1010)(0b0111));
}

TEST(Functional_Placeholder, Bitwise_Or)
{
  ASSERT_TRUE((0b0111 | 0b1010) == (_ | _)(0b0111, 0b1010));
  ASSERT_TRUE((0b0111 | 0b1010) == (0b0111 | _)(0b1010));
  ASSERT_TRUE((0b0111 | 0b1010) == (_ | 0b1010)(0b0111));
}

TEST(Functional_Placeholder, Bitwise_Xor)
{
  ASSERT_TRUE((0b0111 ^ 0b1010) == (_ ^ _)(0b0111, 0b1010));
  ASSERT_TRUE((0b0111 ^ 0b1010) == (0b0111 ^ _)(0b1010));
  ASSERT_TRUE((0b0111 ^ 0b1010) == (_ ^ 0b1010)(0b0111));
}

TEST(Functional_Placeholder, Bitwise_Lshift)
{
  ASSERT_TRUE((0b0111 << 5) == (_ << _)(0b0111, 5));
  ASSERT_TRUE((0b0111 << 5) == (0b0111 << _)(5));
  ASSERT_TRUE((0b0111 << 5) == (_ << 5)(0b0111));
}

TEST(Functional_Placeholder, Bitwise_Rshift)
{
  ASSERT_TRUE((0b0111 >> 5) == (_ >> _)(0b0111, 5));
  ASSERT_TRUE((0b0111 >> 5) == (0b0111 >> _)(5));
  ASSERT_TRUE((0b0111 >> 5) == (_ >> 5)(0b0111));
}

TEST(Functional_Placeholder, Bitwise_Assignement_And)
{
  int a = 0b0101;
  ASSERT_TRUE(&a == &(_ &= _)(a, 0b1011));
  ASSERT_TRUE(a == (0b0101 & 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(a &= _)(0b1011));
  ASSERT_TRUE(a == (0b0101 & 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(_ &= 0b1011)(a));
  ASSERT_TRUE(a == (0b0101 & 0b1011));
}

TEST(Functional_Placeholder, Bitwise_Assignement_Or)
{
  int a = 0b0101;
  ASSERT_TRUE(&a == &(_ |= _)(a, 0b1011));
  ASSERT_TRUE(a == (0b0101 | 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(a |= _)(0b1011));
  ASSERT_TRUE(a == (0b0101 | 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(_ |= 0b1011)(a));
  ASSERT_TRUE(a == (0b0101 | 0b1011));
}

TEST(Functional_Placeholder, Bitwise_Assignement_Xor)
{
  int a = 0b0101;
  ASSERT_TRUE(&a == &(_ ^= _)(a, 0b1011));
  ASSERT_TRUE(a == (0b0101 ^ 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(a ^= _)(0b1011));
  ASSERT_TRUE(a == (0b0101 ^ 0b1011));

  a = 0b0101;
  ASSERT_TRUE(&a == &(_ ^= 0b1011)(a));
  ASSERT_TRUE(a == (0b0101 ^ 0b1011));
}

TEST(Functional_Placeholder, Bitwise_Assignement_Lshift)
{
  int a = 0b0101;
  ASSERT_TRUE(&a == &(_ <<= _)(a, 5));
  ASSERT_TRUE(a == (0b0101 << 5));

  a = 0b0101;
  ASSERT_TRUE(&a == &(a <<= _)(5));
  ASSERT_TRUE(a == (0b0101 << 5));

  a = 0b0101;
  ASSERT_TRUE(&a == &(_ <<= 5)(a));
  ASSERT_TRUE(a == (0b0101 << 5));
}

TEST(Functional_Placeholder, Bitwise_Assignement_Rshift)
{
  int a = 0b0101;
  ASSERT_TRUE(&a == &(_ >>= _)(a, 5));
  ASSERT_TRUE(a == (0b0101 >> 5));

  a = 0b0101;
  ASSERT_TRUE(&a == &(a >>= _)(5));
  ASSERT_TRUE(a == (0b0101 >> 5));

  a = 0b0101;
  ASSERT_TRUE(&a == &(_ >>= 5)(a));
  ASSERT_TRUE(a == (0b0101 >> 5));
}


TEST(Functional_Placeholder, Comparison_Equal)
{
  ASSERT_TRUE((true == false) == (_ == _)(true, false));
  ASSERT_TRUE((true == false) == (true == _)(false));
  ASSERT_TRUE((true == false) == (_ == false)(true));
}

TEST(Functional_Placeholder, Comparison_NotEqual)
{
  ASSERT_TRUE((true != false) == (_ != _)(true, false));
  ASSERT_TRUE((true != false) == (true != _)(false));
  ASSERT_TRUE((true != false) == (_ != false)(true));
}

TEST(Functional_Placeholder, Comparison_LessThan)
{
  ASSERT_TRUE((0 < 5) == (_ < _)(0, 5));
  ASSERT_TRUE((0 < 5) == (0 < _)(5));
  ASSERT_TRUE((0 < 5) == (_ < 5)(0));
}

TEST(Functional_Placeholder, Comparison_LessEqualThan)
{
  ASSERT_TRUE((0 <= 5) == (_ <= _)(0, 5));
  ASSERT_TRUE((0 <= 5) == (0 <= _)(5));
  ASSERT_TRUE((0 <= 5) == (_ <= 5)(0));

  ASSERT_TRUE((5 <= 5) == (_ <= _)(5, 5));
  ASSERT_TRUE((5 <= 5) == (5 <= _)(5));
  ASSERT_TRUE((5 <= 5) == (_ <= 5)(5));
}

TEST(Functional_Placeholder, Comparison_GreaterThan)
{
  ASSERT_TRUE((0 > 5) == (_ > _)(0, 5));
  ASSERT_TRUE((0 > 5) == (0 > _)(5));
  ASSERT_TRUE((0 > 5) == (_ > 5)(0));
}

TEST(Functional_Placeholder, Comparison_GreaterEqualThan)
{
  ASSERT_TRUE((5 >= 5) == (_ >= _)(5, 5));
  ASSERT_TRUE((5 >= 5) == (5 >= _)(5));
  ASSERT_TRUE((5 >= 5) == (_ >= 5)(5));
}


TEST(Functional_Placeholder, Logical_Not)
{
  ASSERT_TRUE((!true) == (!_)(true));
}

TEST(Functional_Placeholder, Logical_And)
{
  ASSERT_TRUE((true && false) == (_ && _)(true, false));
  ASSERT_TRUE((true && false) == (true && _)(false));
  ASSERT_TRUE((true && false) == (_ && false)(true));
}

TEST(Functional_Placeholder, Logical_Or)
{
  ASSERT_TRUE((true || false) == (_ || _)(true, false));
  ASSERT_TRUE((true || false) == (true || _)(false));
  ASSERT_TRUE((true || false) == (_ || false)(true));
}
