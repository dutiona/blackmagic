#include <metaprog/concepts/concepts.hpp>

#include <array>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace concepts = metaprog::concepts;

// member access

struct no_operator_test {
};
struct indirection_test {
  void* operator*()
  {
    return (void*) nullptr;
  }
};

TEST(Cpt_Utility, Indirection)
{
  const int* a = nullptr;
  const int  b = 0;
  ASSERT_TRUE((concepts::Indirection.check<indirection_test>()));
  ASSERT_TRUE((concepts::Indirection.check<decltype(a)>()));
  ASSERT_FALSE((concepts::Indirection.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Indirection.check<decltype(b)>()));
}

struct address_of_test {
  void* operator&()
  {
    return (void*) nullptr;
  }
};

TEST(Cpt_Utility, AddressOf)
{
  const int* a = nullptr;
  const int  b = 0;
  const int& c = b;
  ASSERT_TRUE((concepts::AddressOf.check<address_of_test>()));
  ASSERT_TRUE((concepts::AddressOf.check<decltype(*a)>()));
  ASSERT_TRUE((concepts::AddressOf.check<decltype(c)>()));
#ifndef _MSC_VER // TODO/FIXME remove when reported bug is fixed
  ASSERT_FALSE((concepts::AddressOf.check<no_operator_test>()));
#endif
  ASSERT_FALSE((concepts::AddressOf.check<decltype(a)>()));
  ASSERT_FALSE((concepts::AddressOf.check<decltype(b)>()));
}

struct subscript_test {
  void operator[](int)
  {
  }
};

TEST(Cpt_Utility, Subscript)
{
  std::array<int, 2>  a{{1, 2}};
  std::vector<int>    b{1, 2, 3};
  std::map<int, bool> c{{1, true}, {2, false}};
  int                 d   = 0;
  int                 e[] = {1, 2, 3};
  int*                f   = e;
  ASSERT_TRUE((concepts::Subscript.check<subscript_test, int>()));
  ASSERT_TRUE((concepts::Subscript.check<decltype(a), int>()));
  ASSERT_TRUE((concepts::Subscript.check<decltype(b), int>()));
  ASSERT_TRUE((concepts::Subscript.check<decltype(c), int>()));
  ASSERT_TRUE((concepts::Subscript.check<decltype(e), int>()));
  ASSERT_TRUE((concepts::Subscript.check<decltype(f), int>()));
  ASSERT_FALSE((concepts::Subscript.check<decltype(d), int>()));
  ASSERT_FALSE((concepts::Subscript.check<no_operator_test, int>()));
}

struct pointer_to_member_of_object_test {
  int a;
};
struct pointer_to_member_of_object_other_test {
  int a;
};

TEST(Cpt_Utility, PointerToMemberOfObject)
{
  pointer_to_member_of_object_test obj{};
  ASSERT_TRUE(
    (concepts::PointerToMemberOfObject.check<decltype(obj), decltype(&pointer_to_member_of_object_test::a)>()));
  ASSERT_FALSE(
    (concepts::PointerToMemberOfObject.check<decltype(obj), decltype(&pointer_to_member_of_object_other_test::a)>()));
}

struct pointer_to_member_of_pointer_test {
  int a;
};
struct pointer_to_member_of_pointer_other_test {
  int a;
};

TEST(Cpt_Utility, PointerToMemberOfPointer)
{
  pointer_to_member_of_pointer_test obj{};
  ASSERT_TRUE(
    (concepts::PointerToMemberOfPointer.check<decltype(&obj), decltype(&pointer_to_member_of_pointer_test::a)>()));
  ASSERT_FALSE((
    concepts::PointerToMemberOfPointer.check<decltype(&obj), decltype(&pointer_to_member_of_pointer_other_test::a)>()));
}


// assignement

struct non_assignable_test {
  non_assignable_test& operator=(const non_assignable_test&) = delete;
};
struct assignable_rhs_test {
  struct rhs {
  };
  assignable_rhs_test& operator=(const rhs&)
  {
    return *this;
  }
};
struct int_convertible_test {
  operator int()
  {
    return 0;
  }
};

TEST(Cpt_Utility, Assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::Assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Assignable.check<no_operator_test>()));
  ASSERT_TRUE((concepts::Assignable.check<assignable_rhs_test, assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Assignable.check<decltype(a), int>()));
  ASSERT_FALSE((concepts::Assignable.check<decltype(b), no_operator_test>()));
  ASSERT_FALSE((concepts::Assignable.check<non_assignable_test>()));
}

struct plus_assignable_test {
  plus_assignable_test& operator+=(const plus_assignable_test&)
  {
    return *this;
  }
};
struct plus_assignable_int_test {
  plus_assignable_int_test& operator+=(int)
  {
    return *this;
  }
};
struct plus_assignable_rhs_test {
  struct rhs {
  };
  plus_assignable_rhs_test& operator+=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, PlusAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::PlusAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::PlusAssignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::PlusAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::PlusAssignable.check<plus_assignable_test>()));
  ASSERT_TRUE((concepts::PlusAssignable.check<plus_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::PlusAssignable.check<plus_assignable_rhs_test, plus_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::PlusAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::PlusAssignable.check<decltype(b), plus_assignable_test>()));
  ASSERT_FALSE((concepts::PlusAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::PlusAssignable.check<plus_assignable_int_test>()));
}

struct less_assignable_test {
  less_assignable_test& operator-=(const less_assignable_test&)
  {
    return *this;
  }
};
struct less_assignable_int_test {
  less_assignable_int_test& operator-=(int)
  {
    return *this;
  }
};
struct less_assignable_rhs_test {
  struct rhs {
  };
  less_assignable_rhs_test& operator-=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, LessAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::LessAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::LessAssignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::LessAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::LessAssignable.check<less_assignable_test>()));
  ASSERT_TRUE((concepts::LessAssignable.check<less_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::LessAssignable.check<less_assignable_rhs_test, less_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::LessAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::LessAssignable.check<decltype(b), less_assignable_test>()));
  ASSERT_FALSE((concepts::LessAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::LessAssignable.check<less_assignable_int_test>()));
}

struct mult_assignable_test {
  mult_assignable_test& operator*=(const mult_assignable_test&)
  {
    return *this;
  }
};
struct mult_assignable_int_test {
  mult_assignable_int_test& operator*=(int)
  {
    return *this;
  }
};
struct mult_assignable_rhs_test {
  struct rhs {
  };
  mult_assignable_rhs_test& operator*=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, MultAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::MultAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::MultAssignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::MultAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::MultAssignable.check<mult_assignable_test>()));
  ASSERT_TRUE((concepts::MultAssignable.check<mult_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::MultAssignable.check<mult_assignable_rhs_test, mult_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::MultAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::MultAssignable.check<decltype(b), mult_assignable_test>()));
  ASSERT_FALSE((concepts::MultAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::MultAssignable.check<mult_assignable_int_test>()));
}

struct div_assignable_test {
  div_assignable_test& operator/=(const div_assignable_test&)
  {
    return *this;
  }
};
struct div_assignable_int_test {
  div_assignable_int_test& operator/=(int)
  {
    return *this;
  }
};
struct div_assignable_rhs_test {
  struct rhs {
  };
  div_assignable_rhs_test& operator/=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, DivAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::DivAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::DivAssignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::DivAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::DivAssignable.check<div_assignable_test>()));
  ASSERT_TRUE((concepts::DivAssignable.check<div_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::DivAssignable.check<div_assignable_rhs_test, div_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::DivAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::DivAssignable.check<decltype(b), div_assignable_test>()));
  ASSERT_FALSE((concepts::DivAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::DivAssignable.check<div_assignable_int_test>()));
}

struct mod_assignable_test {
  mod_assignable_test& operator%=(const mod_assignable_test&)
  {
    return *this;
  }
};
struct mod_assignable_int_test {
  mod_assignable_int_test& operator%=(int)
  {
    return *this;
  }
};
struct mod_assignable_rhs_test {
  struct rhs {
  };
  mod_assignable_rhs_test& operator%=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, ModAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::ModAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::ModAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::ModAssignable.check<mod_assignable_test>()));
  ASSERT_TRUE((concepts::ModAssignable.check<mod_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::ModAssignable.check<mod_assignable_rhs_test, mod_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::ModAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::ModAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::ModAssignable.check<decltype(b), mod_assignable_test>()));
  ASSERT_FALSE((concepts::ModAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::ModAssignable.check<mod_assignable_int_test>()));
}

struct and_assignable_test {
  and_assignable_test& operator&=(const and_assignable_test&)
  {
    return *this;
  }
};
struct and_assignable_int_test {
  and_assignable_int_test& operator&=(int)
  {
    return *this;
  }
};
struct and_assignable_rhs_test {
  struct rhs {
  };
  and_assignable_rhs_test& operator&=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, AndAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::AndAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::AndAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::AndAssignable.check<and_assignable_test>()));
  ASSERT_TRUE((concepts::AndAssignable.check<and_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::AndAssignable.check<and_assignable_rhs_test, and_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::AndAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::AndAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::AndAssignable.check<decltype(b), and_assignable_test>()));
  ASSERT_FALSE((concepts::AndAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::AndAssignable.check<and_assignable_int_test>()));
}

struct or_assignable_test {
  or_assignable_test& operator|=(const or_assignable_test&)
  {
    return *this;
  }
};
struct or_assignable_int_test {
  or_assignable_int_test& operator|=(int)
  {
    return *this;
  }
};
struct or_assignable_rhs_test {
  struct rhs {
  };
  or_assignable_rhs_test& operator|=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, OrAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::OrAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::OrAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::OrAssignable.check<or_assignable_test>()));
  ASSERT_TRUE((concepts::OrAssignable.check<or_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::OrAssignable.check<or_assignable_rhs_test, or_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::OrAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::OrAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::OrAssignable.check<decltype(b), or_assignable_test>()));
  ASSERT_FALSE((concepts::OrAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::OrAssignable.check<or_assignable_int_test>()));
}

struct xor_assignable_test {
  xor_assignable_test& operator^=(const xor_assignable_test&)
  {
    return *this;
  }
};
struct xor_assignable_int_test {
  xor_assignable_int_test& operator^=(int)
  {
    return *this;
  }
};
struct xor_assignable_rhs_test {
  struct rhs {
  };
  xor_assignable_rhs_test& operator^=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, XorAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::XorAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::XorAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::XorAssignable.check<xor_assignable_test>()));
  ASSERT_TRUE((concepts::XorAssignable.check<xor_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::XorAssignable.check<xor_assignable_rhs_test, xor_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::XorAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::XorAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::XorAssignable.check<decltype(b), xor_assignable_test>()));
  ASSERT_FALSE((concepts::XorAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::XorAssignable.check<xor_assignable_int_test>()));
}

struct lshift_assignable_test {
  lshift_assignable_test& operator<<=(const lshift_assignable_test&)
  {
    return *this;
  }
};
struct lshift_assignable_int_test {
  lshift_assignable_int_test& operator<<=(int)
  {
    return *this;
  }
};
struct lshift_assignable_rhs_test {
  struct rhs {
  };
  lshift_assignable_rhs_test& operator<<=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, LshiftAssignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::LshiftAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::LshiftAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::LshiftAssignable.check<lshift_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::LshiftAssignable.check<lshift_assignable_rhs_test, lshift_assignable_rhs_test::rhs>()));
  ASSERT_TRUE((concepts::LshiftAssignable.check<lshift_assignable_test>()));
  ASSERT_FALSE((concepts::LshiftAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::LshiftAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::LshiftAssignable.check<decltype(b), lshift_assignable_test>()));
  ASSERT_FALSE((concepts::LshiftAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::LshiftAssignable.check<lshift_assignable_int_test>()));
}

struct rshift_assignable_test {
  rshift_assignable_test& operator>>=(const rshift_assignable_test&)
  {
    return *this;
  }
};
struct rshift_assignable_int_test {
  rshift_assignable_int_test& operator>>=(int)
  {
    return *this;
  }
};
struct rshift_assignable_rhs_test {
  struct rhs {
  };
  rshift_assignable_rhs_test& operator>>=(const rhs&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, rshift_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::RshiftAssignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::RshiftAssignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::RshiftAssignable.check<rshift_assignable_test>()));
  ASSERT_TRUE((concepts::RshiftAssignable.check<rshift_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::RshiftAssignable.check<rshift_assignable_rhs_test, rshift_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::RshiftAssignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::RshiftAssignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::RshiftAssignable.check<decltype(b), rshift_assignable_test>()));
  ASSERT_FALSE((concepts::RshiftAssignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::RshiftAssignable.check<rshift_assignable_int_test>()));
}


// arithmetic

struct positive_test {
  friend positive_test operator+(positive_test lhs)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Positive)
{
  const int a = -1;
  int       b = 0;
  double    c = -3.14;
  ASSERT_TRUE((concepts::Positive.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Positive.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Positive.check<decltype(c)>()));
  ASSERT_TRUE((concepts::Positive.check<positive_test>()));
  ASSERT_FALSE((concepts::Positive.check<no_operator_test>()));
}

struct negative_test {
  friend negative_test operator-(negative_test lhs)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Negative)
{
  const int a = -1;
  int       b = 0;
  double    c = -3.14;
  ASSERT_TRUE((concepts::Negative.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Negative.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Negative.check<decltype(c)>()));
  ASSERT_TRUE((concepts::Negative.check<negative_test>()));
  ASSERT_FALSE((concepts::Negative.check<no_operator_test>()));
}

struct not_test {
  friend not_test operator~(not_test lhs)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, not)
{
  const int a = -1;
  int       b = 0;
  double    c = -3.14;
  ASSERT_TRUE((concepts::Not.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Not.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Not.check<not_test>()));
  ASSERT_FALSE((concepts::Not.check<decltype(c)>()));
  ASSERT_FALSE((concepts::Not.check<no_operator_test>()));
}

struct plus_test {
  friend plus_test operator+(plus_test lhs, const plus_test&)
  {
    return lhs;
  }
};
struct plus_int_test {
  friend plus_int_test operator+(plus_int_test lhs, int)
  {
    return lhs;
  }
};
struct plus_rhs_test {
  struct rhs {
  };
  friend plus_rhs_test operator+(plus_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Plus)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Plus.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Plus.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Plus.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::Plus.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Plus.check<plus_test>()));
  ASSERT_TRUE((concepts::Plus.check<plus_int_test, int>()));
  ASSERT_TRUE((concepts::Plus.check<plus_rhs_test, plus_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Plus.check<decltype(b), plus_test>()));
  ASSERT_FALSE((concepts::Plus.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Plus.check<plus_int_test>()));
}

struct less_test {
  friend less_test operator-(less_test lhs, const less_test&)
  {
    return lhs;
  }
};
struct less_int_test {
  friend less_int_test operator-(less_int_test lhs, int)
  {
    return lhs;
  }
};
struct less_rhs_test {
  struct rhs {
  };
  friend less_rhs_test operator-(less_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Less)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Less.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Less.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Less.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::Less.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Less.check<less_test>()));
  ASSERT_TRUE((concepts::Less.check<less_int_test, int>()));
  ASSERT_TRUE((concepts::Less.check<less_rhs_test, less_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Less.check<decltype(b), less_test>()));
  ASSERT_FALSE((concepts::Less.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Less.check<less_int_test>()));
}

struct mult_test {
  friend mult_test operator*(mult_test lhs, const mult_test&)
  {
    return lhs;
  }
};
struct mult_int_test {
  friend mult_int_test operator*(mult_int_test lhs, int)
  {
    return lhs;
  }
};
struct mult_rhs_test {
  struct rhs {
  };
  friend mult_rhs_test operator*(mult_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Mult)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Mult.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Mult.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Mult.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::Mult.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Mult.check<mult_test>()));
  ASSERT_TRUE((concepts::Mult.check<mult_int_test, int>()));
  ASSERT_TRUE((concepts::Mult.check<mult_rhs_test, mult_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Mult.check<decltype(b), mult_test>()));
  ASSERT_FALSE((concepts::Mult.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Mult.check<mult_int_test>()));
}

struct div_test {
  friend div_test operator/(div_test lhs, const div_test&)
  {
    return lhs;
  }
};
struct div_int_test {
  friend div_int_test operator/(div_int_test lhs, int)
  {
    return lhs;
  }
};
struct div_rhs_test {
  struct rhs {
  };
  friend div_rhs_test operator/(div_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Div)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Div.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Div.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Div.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::Div.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Div.check<div_test>()));
  ASSERT_TRUE((concepts::Div.check<div_int_test, int>()));
  ASSERT_TRUE((concepts::Div.check<div_rhs_test, div_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Div.check<decltype(b), div_test>()));
  ASSERT_FALSE((concepts::Div.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Div.check<div_int_test>()));
}

struct mod_test {
  friend mod_test operator%(mod_test lhs, const mod_test&)
  {
    return lhs;
  }
};
struct mod_int_test {
  friend mod_int_test operator%(mod_int_test lhs, int)
  {
    return lhs;
  }
};
struct mod_rhs_test {
  struct rhs {
  };
  friend mod_rhs_test operator%(mod_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Mod)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Mod.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Mod.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Mod.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Mod.check<mod_test>()));
  ASSERT_TRUE((concepts::Mod.check<mod_int_test, int>()));
  ASSERT_TRUE((concepts::Mod.check<mod_rhs_test, mod_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Mod.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::Mod.check<decltype(b), mod_test>()));
  ASSERT_FALSE((concepts::Mod.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Mod.check<mod_int_test>()));
}

struct and_test {
  friend and_test operator&(and_test lhs, const and_test&)
  {
    return lhs;
  }
};
struct and_int_test {
  friend and_int_test operator&(and_int_test lhs, int)
  {
    return lhs;
  }
};
struct and_rhs_test {
  struct rhs {
  };
  friend and_rhs_test operator&(and_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, and)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::And.check<decltype(a)>()));
  ASSERT_TRUE((concepts::And.check<decltype(b)>()));
  ASSERT_TRUE((concepts::And.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::And.check<and_test>()));
  ASSERT_TRUE((concepts::And.check<and_int_test, int>()));
  ASSERT_TRUE((concepts::And.check<and_rhs_test, and_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::And.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::And.check<decltype(b), and_test>()));
  ASSERT_FALSE((concepts::And.check<no_operator_test>()));
  ASSERT_FALSE((concepts::And.check<and_int_test>()));
}

struct or_test {
  friend or_test operator|(or_test lhs, const or_test&)
  {
    return lhs;
  }
};
struct or_int_test {
  friend or_int_test operator|(or_int_test lhs, int)
  {
    return lhs;
  }
};
struct or_rhs_test {
  struct rhs {
  };
  friend or_rhs_test operator|(or_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, or)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Or.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Or.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Or.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Or.check<or_test>()));
  ASSERT_TRUE((concepts::Or.check<or_int_test, int>()));
  ASSERT_TRUE((concepts::Or.check<or_rhs_test, or_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Or.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::Or.check<decltype(b), or_test>()));
  ASSERT_FALSE((concepts::Or.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Or.check<or_int_test>()));
}

struct xor_test {
  friend xor_test operator^(xor_test lhs, const xor_test&)
  {
    return lhs;
  }
};
struct xor_int_test {
  friend xor_int_test operator^(xor_int_test lhs, int)
  {
    return lhs;
  }
};
struct xor_rhs_test {
  struct rhs {
  };
  friend xor_rhs_test operator^(xor_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, xor)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Xor.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Xor.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Xor.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Xor.check<xor_test>()));
  ASSERT_TRUE((concepts::Xor.check<xor_int_test, int>()));
  ASSERT_TRUE((concepts::Xor.check<xor_rhs_test, xor_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Xor.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::Xor.check<decltype(b), xor_test>()));
  ASSERT_FALSE((concepts::Xor.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Xor.check<xor_int_test>()));
}

struct lshift_test {
  friend lshift_test operator<<(lshift_test lhs, const lshift_test&)
  {
    return lhs;
  }
};
struct lshift_int_test {
  friend lshift_int_test operator<<(lshift_int_test lhs, int)
  {
    return lhs;
  }
};
struct lshift_rhs_test {
  struct rhs {
  };
  friend lshift_rhs_test operator<<(lshift_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Lshift)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Lshift.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Lshift.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Lshift.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Lshift.check<lshift_test>()));
  ASSERT_TRUE((concepts::Lshift.check<lshift_int_test, int>()));
  ASSERT_TRUE((concepts::Lshift.check<lshift_rhs_test, lshift_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Lshift.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::Lshift.check<decltype(b), lshift_test>()));
  ASSERT_FALSE((concepts::Lshift.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Lshift.check<lshift_int_test>()));
}

struct rshift_test {
  friend rshift_test operator>>(rshift_test lhs, const rshift_test&)
  {
    return lhs;
  }
};
struct rshift_int_test {
  friend rshift_int_test operator>>(rshift_int_test lhs, int)
  {
    return lhs;
  }
};
struct rshift_rhs_test {
  struct rhs {
  };
  friend rshift_rhs_test operator>>(rshift_rhs_test lhs, const rhs&)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, Rshift)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::Rshift.check<decltype(a)>()));
  ASSERT_TRUE((concepts::Rshift.check<decltype(b)>()));
  ASSERT_TRUE((concepts::Rshift.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::Rshift.check<rshift_test>()));
  ASSERT_TRUE((concepts::Rshift.check<rshift_int_test, int>()));
  ASSERT_TRUE((concepts::Rshift.check<rshift_rhs_test, rshift_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::Rshift.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::Rshift.check<decltype(b), rshift_test>()));
  ASSERT_FALSE((concepts::Rshift.check<no_operator_test>()));
  ASSERT_FALSE((concepts::Rshift.check<rshift_int_test>()));
}


// increment/decrement

struct pre_incrementable_test {
  pre_incrementable_test& operator++()
  {
    return *this;
  }
};

TEST(Cpt_Utility, PreIncrementable)
{
  const int                    a = 0;
  int                          b = 0;
  const double                 c = 0;
  double                       d = 0;
  const pre_incrementable_test co{};
  ASSERT_TRUE((concepts::PreIncrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::PreIncrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::PreIncrementable.check<pre_incrementable_test>()));
  ASSERT_FALSE((concepts::PreIncrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::PreIncrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::PreIncrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::PreIncrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::PreIncrementable.check<int_convertible_test>()));
}

struct post_incrementable_test {
  post_incrementable_test& operator++(int)
  {
    return *this;
  }
};

TEST(Cpt_Utility, PostIncrementable)
{
  const int                     a = 0;
  int                           b = 0;
  const double                  c = 0;
  double                        d = 0;
  const post_incrementable_test co{};
  ASSERT_TRUE((concepts::PostIncrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::PostIncrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::PostIncrementable.check<post_incrementable_test>()));
  ASSERT_FALSE((concepts::PostIncrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::PostIncrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::PostIncrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::PostIncrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::PostIncrementable.check<int_convertible_test>()));
}

struct pre_decrementable_test {
  pre_decrementable_test& operator--()
  {
    return *this;
  }
};

TEST(Cpt_Utility, PreDecrementable)
{
  const int                    a = 0;
  int                          b = 0;
  const double                 c = 0;
  double                       d = 0;
  const pre_decrementable_test co{};
  ASSERT_TRUE((concepts::PreDecrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::PreDecrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::PreDecrementable.check<pre_decrementable_test>()));
  ASSERT_FALSE((concepts::PreDecrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::PreDecrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::PreDecrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::PreDecrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::PreDecrementable.check<int_convertible_test>()));
}

struct post_decrementable_test {
  post_decrementable_test& operator--(int)
  {
    return *this;
  }
};

TEST(Cpt_Utility, PostDecrementable)
{
  const int                     a = 0;
  int                           b = 0;
  const double                  c = 0;
  double                        d = 0;
  const post_decrementable_test co{};
  ASSERT_TRUE((concepts::PostDecrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::PostDecrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::PostDecrementable.check<post_decrementable_test>()));
  ASSERT_FALSE((concepts::PostDecrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::PostDecrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::PostDecrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::PostDecrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::PostDecrementable.check<int_convertible_test>()));
}


// comparison

struct bool_convertible_test {
  operator bool()
  {
    return true;
  }
};

struct equality_op_member_test {
  bool operator==(int)
  {
    return false;
  }
};
struct equality_op_friend_test {
  friend bool operator==(const equality_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator==(int lhs, const equality_op_friend_test& rhs)
  {
    return rhs == lhs;
  }
};

TEST(Cpt_Utility, Equality)
{
  ASSERT_TRUE((concepts::Equality.check<equality_op_member_test, int>()));
  ASSERT_TRUE((concepts::Equality.check<equality_op_friend_test, int>()));
  ASSERT_TRUE((concepts::Equality.check<int, equality_op_friend_test>()));
  ASSERT_TRUE((concepts::Equality.check<bool, int>()));
  ASSERT_TRUE((concepts::Equality.check<double, int>()));
  ASSERT_TRUE((concepts::Equality.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::Equality.check<int, equality_op_member_test>()));
  ASSERT_FALSE((concepts::Equality.check<no_operator_test, no_operator_test>()));
}

struct inequality_op_member_test {
  bool operator!=(int)
  {
    return false;
  }
};
struct inequality_op_friend_test {
  friend bool operator!=(const inequality_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator!=(int lhs, const inequality_op_friend_test& rhs)
  {
    return rhs != lhs;
  }
};

TEST(Cpt_Utility, Inequality)
{
  ASSERT_TRUE((concepts::Inequality.check<inequality_op_member_test, int>()));
  ASSERT_TRUE((concepts::Inequality.check<inequality_op_friend_test, int>()));
  ASSERT_TRUE((concepts::Inequality.check<int, inequality_op_friend_test>()));
  ASSERT_TRUE((concepts::Inequality.check<bool, int>()));
  ASSERT_TRUE((concepts::Inequality.check<double, int>()));
  ASSERT_TRUE((concepts::Inequality.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::Inequality.check<int, inequality_op_member_test>()));
  ASSERT_FALSE((concepts::Inequality.check<no_operator_test, no_operator_test>()));
}

struct less_than_op_member_test {
  bool operator<(int)
  {
    return false;
  }
};
struct less_than_op_friend_test {
  friend bool operator<(const less_than_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator<(int lhs, const less_than_op_friend_test& rhs)
  {
    return rhs < lhs;
  }
};

TEST(Cpt_Utility, LessThan)
{
  ASSERT_TRUE((concepts::LessThan.check<less_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::LessThan.check<less_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::LessThan.check<int, less_than_op_friend_test>()));
  ASSERT_TRUE((concepts::LessThan.check<bool, int>()));
  ASSERT_TRUE((concepts::LessThan.check<double, int>()));
  ASSERT_TRUE((concepts::LessThan.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::LessThan.check<int, less_than_op_member_test>()));
  ASSERT_FALSE((concepts::LessThan.check<no_operator_test, no_operator_test>()));
}

struct less_equal_than_op_member_test {
  bool operator<=(int)
  {
    return false;
  }
};
struct less_equal_than_op_friend_test {
  friend bool operator<=(const less_equal_than_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator<=(int lhs, const less_equal_than_op_friend_test& rhs)
  {
    return rhs <= lhs;
  }
};

TEST(Cpt_Utility, LessEqualThan)
{
  ASSERT_TRUE((concepts::LessEqualThan.check<less_equal_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::LessEqualThan.check<less_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::LessEqualThan.check<int, less_equal_than_op_friend_test>()));
  ASSERT_TRUE((concepts::LessEqualThan.check<bool, int>()));
  ASSERT_TRUE((concepts::LessEqualThan.check<double, int>()));
  ASSERT_TRUE((concepts::LessEqualThan.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::LessEqualThan.check<int, less_equal_than_op_member_test>()));
  ASSERT_FALSE((concepts::LessEqualThan.check<no_operator_test, no_operator_test>()));
}

struct greater_than_op_member_test {
  bool operator>(int)
  {
    return false;
  }
};
struct greater_than_op_friend_test {
  friend bool operator>(const greater_than_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator>(int lhs, const greater_than_op_friend_test& rhs)
  {
    return rhs > lhs;
  }
};

TEST(Cpt_Utility, GreaterThan)
{
  ASSERT_TRUE((concepts::GreaterThan.check<greater_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::GreaterThan.check<greater_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::GreaterThan.check<int, greater_than_op_friend_test>()));
  ASSERT_TRUE((concepts::GreaterThan.check<bool, int>()));
  ASSERT_TRUE((concepts::GreaterThan.check<double, int>()));
  ASSERT_TRUE((concepts::GreaterThan.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::GreaterThan.check<int, greater_than_op_member_test>()));
  ASSERT_FALSE((concepts::GreaterThan.check<no_operator_test, no_operator_test>()));
}

struct greater_equal_than_op_member_test {
  bool operator>=(int)
  {
    return false;
  }
};
struct greater_equal_than_op_friend_test {
  friend bool operator>=(const greater_equal_than_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator>=(int lhs, const greater_equal_than_op_friend_test& rhs)
  {
    return rhs >= lhs;
  }
};

TEST(Cpt_Utility, GreaterEqualThan)
{
  ASSERT_TRUE((concepts::GreaterEqualThan.check<greater_equal_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::GreaterEqualThan.check<greater_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::GreaterEqualThan.check<int, greater_equal_than_op_friend_test>()));
  ASSERT_TRUE((concepts::GreaterEqualThan.check<bool, int>()));
  ASSERT_TRUE((concepts::GreaterEqualThan.check<double, int>()));
  ASSERT_TRUE((concepts::GreaterEqualThan.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::GreaterEqualThan.check<int, greater_equal_than_op_member_test>()));
  ASSERT_FALSE((concepts::GreaterEqualThan.check<no_operator_test, no_operator_test>()));
}


// logical

struct logical_not_test {
  logical_not_test& operator!()
  {
    return *this;
  }
};

TEST(Cpt_Utility, LogicalNot)
{
  ASSERT_TRUE((concepts::LogicalNot.check<logical_not_test>()));
  ASSERT_TRUE((concepts::LogicalNot.check<bool>()));
  ASSERT_TRUE((concepts::LogicalNot.check<int>()));
  ASSERT_TRUE((concepts::LogicalNot.check<decltype(!std::declval<int>())>()));
  ASSERT_FALSE((concepts::LogicalNot.check<no_operator_test>()));
}

struct logical_and_op_member_test {
  bool operator&&(int)
  {
    return false;
  }
};
struct logical_and_op_friend_test {
  friend bool operator&&(const logical_and_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator&&(int lhs, const logical_and_op_friend_test& rhs)
  {
    return rhs && lhs;
  }
};

TEST(Cpt_Utility, LogicalAnd)
{
  ASSERT_TRUE((concepts::LogicalAnd.check<logical_and_op_member_test, int>()));
  ASSERT_TRUE((concepts::LogicalAnd.check<logical_and_op_friend_test, int>()));
  ASSERT_TRUE((concepts::LogicalAnd.check<int, logical_and_op_friend_test>()));
  ASSERT_TRUE((concepts::LogicalAnd.check<bool, int>()));
  ASSERT_TRUE((concepts::LogicalAnd.check<double, int>()));
  ASSERT_TRUE((concepts::LogicalAnd.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::LogicalAnd.check<int, logical_and_op_member_test>()));
  ASSERT_FALSE((concepts::LogicalAnd.check<no_operator_test, no_operator_test>()));
}

struct logical_or_op_member_test {
  bool operator||(int)
  {
    return false;
  }
};
struct logical_or_op_friend_test {
  friend bool operator||(const logical_or_op_friend_test&, int)
  {
    return true;
  }
  friend bool operator||(int lhs, const logical_or_op_friend_test& rhs)
  {
    return rhs || lhs;
  }
};

TEST(Cpt_Utility, LogicalOr)
{
  ASSERT_TRUE((concepts::LogicalOr.check<logical_or_op_member_test, int>()));
  ASSERT_TRUE((concepts::LogicalOr.check<logical_or_op_friend_test, int>()));
  ASSERT_TRUE((concepts::LogicalOr.check<int, logical_or_op_friend_test>()));
  ASSERT_TRUE((concepts::LogicalOr.check<bool, int>()));
  ASSERT_TRUE((concepts::LogicalOr.check<double, int>()));
  ASSERT_TRUE((concepts::LogicalOr.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::LogicalOr.check<int, logical_or_op_member_test>()));
  ASSERT_FALSE((concepts::LogicalOr.check<no_operator_test, no_operator_test>()));
}


// other

struct comma_restrict_test {
  struct rhs {
  };
  // Forbid comma operator for all except rhs
  template <typename T, std::enable_if_t<!std::is_same_v<T, rhs>>* = nullptr>
  comma_restrict_test& operator,(T&&) = delete;
  // Allow for a subset
  template <typename T, std::enable_if_t<std::is_same_v<T, rhs>>* = nullptr>
  comma_restrict_test& operator,(T&&)
  {
    return *this;
  }
};

TEST(Cpt_Utility, Comma)
{
  ASSERT_FALSE((concepts::Comma.check<comma_restrict_test, int>()));
  ASSERT_TRUE((concepts::Comma.check<comma_restrict_test, comma_restrict_test::rhs>()));
  ASSERT_TRUE((concepts::Comma.check<no_operator_test, int>()));
}

TEST(Cpt_Utility, Ternary)
{
  ASSERT_TRUE((concepts::Ternary.check<bool, int, const double>()));
  ASSERT_TRUE((concepts::Ternary.check<bool, const volatile int, float>()));
  ASSERT_TRUE((concepts::Ternary.check<bool_convertible_test, int_convertible_test, double>()));
  ASSERT_FALSE((concepts::Ternary.check<bool, no_operator_test, no_operator_test>()));
  ASSERT_FALSE((concepts::Ternary.check<bool, no_operator_test, bool>()));
  ASSERT_FALSE((concepts::Ternary.check<bool, std::map<int, double>, std::vector<int>>()));
  ASSERT_FALSE((concepts::Ternary.check<bool_convertible_test, std::vector<float>, const float>()));
}

void invocable_test()
{
}

void invocable_int_test(int)
{
}

int invocable_r_test()
{
  return 0;
}

int invocable_r_double_test(double)
{
  return 0;
}

struct invocable_functor_test {
  void operator()(int, double)
  {
  }
};

struct invocable_r_functor_test {
  std::tuple<int, double> operator()(int, double)
  {
    return {0, 0.};
  }
};

struct invocable_nested_functor_test {
  void test(int, double)
  {
  }
};

struct invocable_nested_r_functor_test {
  std::tuple<int, double> test(int, double)
  {
    return {0, 0.};
  }
};

TEST(Cpt_Utility, Invocable)
{
  static const auto a = 1.5;
  EXPECT_TRUE((concepts::Invocable.check<decltype(invocable_test)>()));
  EXPECT_TRUE((concepts::Invocable.check<decltype(invocable_int_test), int>()));
  EXPECT_TRUE((concepts::Invocable.check<decltype(invocable_r_test)>()));
  EXPECT_TRUE((concepts::Invocable.check<decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::Invocable.check<invocable_functor_test, int, double>()));
  EXPECT_TRUE((concepts::Invocable.check<invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::Invocable
                 .check<decltype(&invocable_nested_functor_test::test), invocable_nested_functor_test, int, double>()));
  EXPECT_TRUE(
    (concepts::Invocable
       .check<decltype(&invocable_nested_r_functor_test::test), invocable_nested_r_functor_test, int, double>()));
  EXPECT_FALSE((concepts::Invocable.check<decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((concepts::Invocable.check<decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((concepts::Invocable.check<decltype(a)>()));
  EXPECT_FALSE((concepts::Invocable.check<invocable_r_functor_test, std::vector<double>>()));
}

TEST(Cpt_Utility, InvocableR)
{
  EXPECT_TRUE((concepts::InvocableR.check<int, decltype(invocable_r_test)>()));
  EXPECT_TRUE((concepts::InvocableR.check<int, decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::InvocableR.check<double, decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::InvocableR.check<std::tuple<int, double>, invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::InvocableR.check<std::tuple<double, double>, invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::InvocableR.check<std::tuple<double, double>, decltype(&invocable_nested_r_functor_test::test),
                                          invocable_nested_r_functor_test, int, double>()));
  EXPECT_FALSE((concepts::InvocableR.check<std::vector<double>, decltype(invocable_r_double_test), double>()));
  EXPECT_FALSE((concepts::InvocableR.check<int, invocable_functor_test, int, double>()));
}
