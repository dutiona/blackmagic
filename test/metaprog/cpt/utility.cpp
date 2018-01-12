#include <metaprog/cpt/cpt.hpp>

#include <array>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

// member access

struct no_operator_test {
};
struct indirection_test {
  void* operator*()
  {
    return (void*) nullptr;
  }
};

TEST(Cpt_Utility, indirection)
{
  const int* a = nullptr;
  const int  b = 0;
  ASSERT_TRUE((concepts::indirection.check<indirection_test>()));
  ASSERT_TRUE((concepts::indirection.check<decltype(a)>()));
  ASSERT_FALSE((concepts::indirection.check<no_operator_test>()));
  ASSERT_FALSE((concepts::indirection.check<decltype(b)>()));
}

struct address_of_test {
  void* operator&()
  {
    return (void*) nullptr;
  }
};

TEST(Cpt_Utility, address_of)
{
  const int* a = nullptr;
  const int  b = 0;
  const int& c = b;
  ASSERT_TRUE((concepts::address_of.check<address_of_test>()));
  ASSERT_TRUE((concepts::address_of.check<decltype(*a)>()));
  ASSERT_TRUE((concepts::address_of.check<decltype(c)>()));
#ifndef _MSC_VER // TODO/FIXME remove when reported bug is fixed
  ASSERT_FALSE((concepts::address_of.check<no_operator_test>()));
#endif
  ASSERT_FALSE((concepts::address_of.check<decltype(a)>()));
  ASSERT_FALSE((concepts::address_of.check<decltype(b)>()));
}

struct subscript_test {
  void operator[](int)
  {
  }
};

TEST(Cpt_Utility, subscript)
{
  std::array<int, 2>  a{{1, 2}};
  std::vector<int>    b{1, 2, 3};
  std::map<int, bool> c{{1, true}, {2, false}};
  int                 d   = 0;
  int                 e[] = {1, 2, 3};
  int*                f   = e;
  ASSERT_TRUE((concepts::subscript.check<subscript_test, int>()));
  ASSERT_TRUE((concepts::subscript.check<decltype(a), int>()));
  ASSERT_TRUE((concepts::subscript.check<decltype(b), int>()));
  ASSERT_TRUE((concepts::subscript.check<decltype(c), int>()));
  ASSERT_TRUE((concepts::subscript.check<decltype(e), int>()));
  ASSERT_TRUE((concepts::subscript.check<decltype(f), int>()));
  ASSERT_FALSE((concepts::subscript.check<decltype(d), int>()));
  ASSERT_FALSE((concepts::subscript.check<no_operator_test, int>()));
}

struct pointer_to_member_of_object_test {
  int a;
};
struct pointer_to_member_of_object_other_test {
  int a;
};

TEST(Cpt_Utility, pointer_to_member_of_object)
{
  pointer_to_member_of_object_test obj{};
  ASSERT_TRUE(
    (concepts::pointer_to_member_of_object.check<decltype(obj), decltype(&pointer_to_member_of_object_test::a)>()));
  ASSERT_FALSE((concepts::pointer_to_member_of_object
                  .check<decltype(obj), decltype(&pointer_to_member_of_object_other_test::a)>()));
}

struct pointer_to_member_of_pointer_test {
  int a;
};
struct pointer_to_member_of_pointer_other_test {
  int a;
};

TEST(Cpt_Utility, pointer_to_member_of_pointer)
{
  pointer_to_member_of_pointer_test obj{};
  ASSERT_TRUE(
    (concepts::pointer_to_member_of_pointer.check<decltype(&obj), decltype(&pointer_to_member_of_pointer_test::a)>()));
  ASSERT_FALSE((concepts::pointer_to_member_of_pointer
                  .check<decltype(&obj), decltype(&pointer_to_member_of_pointer_other_test::a)>()));
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

TEST(Cpt_Utility, assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::assignable.check<no_operator_test>()));
  ASSERT_TRUE((concepts::assignable.check<assignable_rhs_test, assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::assignable.check<decltype(a), int>()));
  ASSERT_FALSE((concepts::assignable.check<decltype(b), no_operator_test>()));
  ASSERT_FALSE((concepts::assignable.check<non_assignable_test>()));
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

TEST(Cpt_Utility, plus_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::plus_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::plus_assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::plus_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::plus_assignable.check<plus_assignable_test>()));
  ASSERT_TRUE((concepts::plus_assignable.check<plus_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::plus_assignable.check<plus_assignable_rhs_test, plus_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::plus_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::plus_assignable.check<decltype(b), plus_assignable_test>()));
  ASSERT_FALSE((concepts::plus_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::plus_assignable.check<plus_assignable_int_test>()));
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

TEST(Cpt_Utility, less_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::less_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::less_assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::less_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::less_assignable.check<less_assignable_test>()));
  ASSERT_TRUE((concepts::less_assignable.check<less_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::less_assignable.check<less_assignable_rhs_test, less_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::less_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::less_assignable.check<decltype(b), less_assignable_test>()));
  ASSERT_FALSE((concepts::less_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::less_assignable.check<less_assignable_int_test>()));
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

TEST(Cpt_Utility, mult_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::mult_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::mult_assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::mult_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::mult_assignable.check<mult_assignable_test>()));
  ASSERT_TRUE((concepts::mult_assignable.check<mult_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::mult_assignable.check<mult_assignable_rhs_test, mult_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::mult_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::mult_assignable.check<decltype(b), mult_assignable_test>()));
  ASSERT_FALSE((concepts::mult_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::mult_assignable.check<mult_assignable_int_test>()));
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

TEST(Cpt_Utility, div_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::div_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::div_assignable.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::div_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::div_assignable.check<div_assignable_test>()));
  ASSERT_TRUE((concepts::div_assignable.check<div_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::div_assignable.check<div_assignable_rhs_test, div_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::div_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::div_assignable.check<decltype(b), div_assignable_test>()));
  ASSERT_FALSE((concepts::div_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::div_assignable.check<div_assignable_int_test>()));
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

TEST(Cpt_Utility, mod_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::mod_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::mod_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::mod_assignable.check<mod_assignable_test>()));
  ASSERT_TRUE((concepts::mod_assignable.check<mod_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::mod_assignable.check<mod_assignable_rhs_test, mod_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::mod_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::mod_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::mod_assignable.check<decltype(b), mod_assignable_test>()));
  ASSERT_FALSE((concepts::mod_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::mod_assignable.check<mod_assignable_int_test>()));
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

TEST(Cpt_Utility, and_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::and_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::and_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::and_assignable.check<and_assignable_test>()));
  ASSERT_TRUE((concepts::and_assignable.check<and_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::and_assignable.check<and_assignable_rhs_test, and_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::and_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::and_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::and_assignable.check<decltype(b), and_assignable_test>()));
  ASSERT_FALSE((concepts::and_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::and_assignable.check<and_assignable_int_test>()));
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

TEST(Cpt_Utility, or_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::or_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::or_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::or_assignable.check<or_assignable_test>()));
  ASSERT_TRUE((concepts::or_assignable.check<or_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::or_assignable.check<or_assignable_rhs_test, or_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::or_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::or_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::or_assignable.check<decltype(b), or_assignable_test>()));
  ASSERT_FALSE((concepts::or_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::or_assignable.check<or_assignable_int_test>()));
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

TEST(Cpt_Utility, xor_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::xor_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::xor_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::xor_assignable.check<xor_assignable_test>()));
  ASSERT_TRUE((concepts::xor_assignable.check<xor_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::xor_assignable.check<xor_assignable_rhs_test, xor_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::xor_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::xor_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::xor_assignable.check<decltype(b), xor_assignable_test>()));
  ASSERT_FALSE((concepts::xor_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::xor_assignable.check<xor_assignable_int_test>()));
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

TEST(Cpt_Utility, lshift_assignable)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::lshift_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::lshift_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::lshift_assignable.check<lshift_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::lshift_assignable.check<lshift_assignable_rhs_test, lshift_assignable_rhs_test::rhs>()));
  ASSERT_TRUE((concepts::lshift_assignable.check<lshift_assignable_test>()));
  ASSERT_FALSE((concepts::lshift_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::lshift_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::lshift_assignable.check<decltype(b), lshift_assignable_test>()));
  ASSERT_FALSE((concepts::lshift_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::lshift_assignable.check<lshift_assignable_int_test>()));
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
  ASSERT_TRUE((concepts::rshift_assignable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::rshift_assignable.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::rshift_assignable.check<rshift_assignable_test>()));
  ASSERT_TRUE((concepts::rshift_assignable.check<rshift_assignable_int_test, int>()));
  ASSERT_TRUE((concepts::rshift_assignable.check<rshift_assignable_rhs_test, rshift_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::rshift_assignable.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::rshift_assignable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::rshift_assignable.check<decltype(b), rshift_assignable_test>()));
  ASSERT_FALSE((concepts::rshift_assignable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::rshift_assignable.check<rshift_assignable_int_test>()));
}


// arithmetic

struct positive_test {
  friend positive_test operator+(positive_test lhs)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, positive)
{
  const int a = -1;
  int       b = 0;
  double    c = -3.14;
  ASSERT_TRUE((concepts::positive.check<decltype(a)>()));
  ASSERT_TRUE((concepts::positive.check<decltype(b)>()));
  ASSERT_TRUE((concepts::positive.check<decltype(c)>()));
  ASSERT_TRUE((concepts::positive.check<positive_test>()));
  ASSERT_FALSE((concepts::positive.check<no_operator_test>()));
}

struct negative_test {
  friend negative_test operator-(negative_test lhs)
  {
    return lhs;
  }
};

TEST(Cpt_Utility, negative)
{
  const int a = -1;
  int       b = 0;
  double    c = -3.14;
  ASSERT_TRUE((concepts::negative.check<decltype(a)>()));
  ASSERT_TRUE((concepts::negative.check<decltype(b)>()));
  ASSERT_TRUE((concepts::negative.check<decltype(c)>()));
  ASSERT_TRUE((concepts::negative.check<negative_test>()));
  ASSERT_FALSE((concepts::negative.check<no_operator_test>()));
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

TEST(Cpt_Utility, plus)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::plus.check<decltype(a)>()));
  ASSERT_TRUE((concepts::plus.check<decltype(b)>()));
  ASSERT_TRUE((concepts::plus.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::plus.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::plus.check<plus_test>()));
  ASSERT_TRUE((concepts::plus.check<plus_int_test, int>()));
  ASSERT_TRUE((concepts::plus.check<plus_rhs_test, plus_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::plus.check<decltype(b), plus_test>()));
  ASSERT_FALSE((concepts::plus.check<no_operator_test>()));
  ASSERT_FALSE((concepts::plus.check<plus_int_test>()));
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

TEST(Cpt_Utility, less)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::less.check<decltype(a)>()));
  ASSERT_TRUE((concepts::less.check<decltype(b)>()));
  ASSERT_TRUE((concepts::less.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::less.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::less.check<less_test>()));
  ASSERT_TRUE((concepts::less.check<less_int_test, int>()));
  ASSERT_TRUE((concepts::less.check<less_rhs_test, less_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::less.check<decltype(b), less_test>()));
  ASSERT_FALSE((concepts::less.check<no_operator_test>()));
  ASSERT_FALSE((concepts::less.check<less_int_test>()));
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

TEST(Cpt_Utility, mult)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::mult.check<decltype(a)>()));
  ASSERT_TRUE((concepts::mult.check<decltype(b)>()));
  ASSERT_TRUE((concepts::mult.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::mult.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::mult.check<mult_test>()));
  ASSERT_TRUE((concepts::mult.check<mult_int_test, int>()));
  ASSERT_TRUE((concepts::mult.check<mult_rhs_test, mult_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::mult.check<decltype(b), mult_test>()));
  ASSERT_FALSE((concepts::mult.check<no_operator_test>()));
  ASSERT_FALSE((concepts::mult.check<mult_int_test>()));
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

TEST(Cpt_Utility, div)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::div.check<decltype(a)>()));
  ASSERT_TRUE((concepts::div.check<decltype(b)>()));
  ASSERT_TRUE((concepts::div.check<decltype(b), double>()));
  ASSERT_TRUE((concepts::div.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::div.check<div_test>()));
  ASSERT_TRUE((concepts::div.check<div_int_test, int>()));
  ASSERT_TRUE((concepts::div.check<div_rhs_test, div_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::div.check<decltype(b), div_test>()));
  ASSERT_FALSE((concepts::div.check<no_operator_test>()));
  ASSERT_FALSE((concepts::div.check<div_int_test>()));
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

TEST(Cpt_Utility, mod)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::mod.check<decltype(a)>()));
  ASSERT_TRUE((concepts::mod.check<decltype(b)>()));
  ASSERT_TRUE((concepts::mod.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::mod.check<mod_test>()));
  ASSERT_TRUE((concepts::mod.check<mod_int_test, int>()));
  ASSERT_TRUE((concepts::mod.check<mod_rhs_test, mod_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::mod.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::mod.check<decltype(b), mod_test>()));
  ASSERT_FALSE((concepts::mod.check<no_operator_test>()));
  ASSERT_FALSE((concepts::mod.check<mod_int_test>()));
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

TEST(Cpt_Utility, lshift)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::lshift.check<decltype(a)>()));
  ASSERT_TRUE((concepts::lshift.check<decltype(b)>()));
  ASSERT_TRUE((concepts::lshift.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::lshift.check<lshift_test>()));
  ASSERT_TRUE((concepts::lshift.check<lshift_int_test, int>()));
  ASSERT_TRUE((concepts::lshift.check<lshift_rhs_test, lshift_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::lshift.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::lshift.check<decltype(b), lshift_test>()));
  ASSERT_FALSE((concepts::lshift.check<no_operator_test>()));
  ASSERT_FALSE((concepts::lshift.check<lshift_int_test>()));
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

TEST(Cpt_Utility, rshift)
{
  const int a = 0;
  int       b = 0;
  ASSERT_TRUE((concepts::rshift.check<decltype(a)>()));
  ASSERT_TRUE((concepts::rshift.check<decltype(b)>()));
  ASSERT_TRUE((concepts::rshift.check<decltype(b), int_convertible_test>()));
  ASSERT_TRUE((concepts::rshift.check<rshift_test>()));
  ASSERT_TRUE((concepts::rshift.check<rshift_int_test, int>()));
  ASSERT_TRUE((concepts::rshift.check<rshift_rhs_test, rshift_rhs_test::rhs>()));
  ASSERT_FALSE((concepts::rshift.check<decltype(b), double>()));
  ASSERT_FALSE((concepts::rshift.check<decltype(b), rshift_test>()));
  ASSERT_FALSE((concepts::rshift.check<no_operator_test>()));
  ASSERT_FALSE((concepts::rshift.check<rshift_int_test>()));
}


// increment/decrement

struct pre_incrementable_test {
  pre_incrementable_test& operator++()
  {
    return *this;
  }
};

TEST(Cpt_Utility, pre_incrementable)
{
  const int                    a = 0;
  int                          b = 0;
  const double                 c = 0;
  double                       d = 0;
  const pre_incrementable_test co{};
  ASSERT_TRUE((concepts::pre_incrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::pre_incrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::pre_incrementable.check<pre_incrementable_test>()));
  ASSERT_FALSE((concepts::pre_incrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::pre_incrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::pre_incrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::pre_incrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::pre_incrementable.check<int_convertible_test>()));
}

struct post_incrementable_test {
  post_incrementable_test& operator++(int)
  {
    return *this;
  }
};

TEST(Cpt_Utility, post_incrementable)
{
  const int                     a = 0;
  int                           b = 0;
  const double                  c = 0;
  double                        d = 0;
  const post_incrementable_test co{};
  ASSERT_TRUE((concepts::post_incrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::post_incrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::post_incrementable.check<post_incrementable_test>()));
  ASSERT_FALSE((concepts::post_incrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::post_incrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::post_incrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::post_incrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::post_incrementable.check<int_convertible_test>()));
}

struct pre_decrementable_test {
  pre_decrementable_test& operator--()
  {
    return *this;
  }
};

TEST(Cpt_Utility, pre_decrementable)
{
  const int                    a = 0;
  int                          b = 0;
  const double                 c = 0;
  double                       d = 0;
  const pre_decrementable_test co{};
  ASSERT_TRUE((concepts::pre_decrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::pre_decrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::pre_decrementable.check<pre_decrementable_test>()));
  ASSERT_FALSE((concepts::pre_decrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::pre_decrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::pre_decrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::pre_decrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::pre_decrementable.check<int_convertible_test>()));
}

struct post_decrementable_test {
  post_decrementable_test& operator--(int)
  {
    return *this;
  }
};

TEST(Cpt_Utility, post_decrementable)
{
  const int                     a = 0;
  int                           b = 0;
  const double                  c = 0;
  double                        d = 0;
  const post_decrementable_test co{};
  ASSERT_TRUE((concepts::post_decrementable.check<decltype(b)>()));
  ASSERT_TRUE((concepts::post_decrementable.check<decltype(d)>()));
  ASSERT_TRUE((concepts::post_decrementable.check<post_decrementable_test>()));
  ASSERT_FALSE((concepts::post_decrementable.check<decltype(a)>()));
  ASSERT_FALSE((concepts::post_decrementable.check<decltype(c)>()));
  ASSERT_FALSE((concepts::post_decrementable.check<decltype(co)>()));
  ASSERT_FALSE((concepts::post_decrementable.check<no_operator_test>()));
  ASSERT_FALSE((concepts::post_decrementable.check<int_convertible_test>()));
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

TEST(Cpt_Utility, equality)
{
  ASSERT_TRUE((concepts::equality.check<equality_op_member_test, int>()));
  ASSERT_TRUE((concepts::equality.check<equality_op_friend_test, int>()));
  ASSERT_TRUE((concepts::equality.check<int, equality_op_friend_test>()));
  ASSERT_TRUE((concepts::equality.check<bool, int>()));
  ASSERT_TRUE((concepts::equality.check<double, int>()));
  ASSERT_TRUE((concepts::equality.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::equality.check<int, equality_op_member_test>()));
  ASSERT_FALSE((concepts::equality.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, inequality)
{
  ASSERT_TRUE((concepts::inequality.check<inequality_op_member_test, int>()));
  ASSERT_TRUE((concepts::inequality.check<inequality_op_friend_test, int>()));
  ASSERT_TRUE((concepts::inequality.check<int, inequality_op_friend_test>()));
  ASSERT_TRUE((concepts::inequality.check<bool, int>()));
  ASSERT_TRUE((concepts::inequality.check<double, int>()));
  ASSERT_TRUE((concepts::inequality.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::inequality.check<int, inequality_op_member_test>()));
  ASSERT_FALSE((concepts::inequality.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, less_than)
{
  ASSERT_TRUE((concepts::less_than.check<less_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::less_than.check<less_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::less_than.check<int, less_than_op_friend_test>()));
  ASSERT_TRUE((concepts::less_than.check<bool, int>()));
  ASSERT_TRUE((concepts::less_than.check<double, int>()));
  ASSERT_TRUE((concepts::less_than.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::less_than.check<int, less_than_op_member_test>()));
  ASSERT_FALSE((concepts::less_than.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, less_equal_than)
{
  ASSERT_TRUE((concepts::less_equal_than.check<less_equal_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::less_equal_than.check<less_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::less_equal_than.check<int, less_equal_than_op_friend_test>()));
  ASSERT_TRUE((concepts::less_equal_than.check<bool, int>()));
  ASSERT_TRUE((concepts::less_equal_than.check<double, int>()));
  ASSERT_TRUE((concepts::less_equal_than.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::less_equal_than.check<int, less_equal_than_op_member_test>()));
  ASSERT_FALSE((concepts::less_equal_than.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, greater_than)
{
  ASSERT_TRUE((concepts::greater_than.check<greater_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::greater_than.check<greater_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::greater_than.check<int, greater_than_op_friend_test>()));
  ASSERT_TRUE((concepts::greater_than.check<bool, int>()));
  ASSERT_TRUE((concepts::greater_than.check<double, int>()));
  ASSERT_TRUE((concepts::greater_than.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::greater_than.check<int, greater_than_op_member_test>()));
  ASSERT_FALSE((concepts::greater_than.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, greater_equal_than)
{
  ASSERT_TRUE((concepts::greater_equal_than.check<greater_equal_than_op_member_test, int>()));
  ASSERT_TRUE((concepts::greater_equal_than.check<greater_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((concepts::greater_equal_than.check<int, greater_equal_than_op_friend_test>()));
  ASSERT_TRUE((concepts::greater_equal_than.check<bool, int>()));
  ASSERT_TRUE((concepts::greater_equal_than.check<double, int>()));
  ASSERT_TRUE((concepts::greater_equal_than.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::greater_equal_than.check<int, greater_equal_than_op_member_test>()));
  ASSERT_FALSE((concepts::greater_equal_than.check<no_operator_test, no_operator_test>()));
}


// logical

struct logical_not_test {
  logical_not_test& operator!()
  {
    return *this;
  }
};

TEST(Cpt_Utility, logical_not)
{
  ASSERT_TRUE((concepts::logical_not.check<logical_not_test>()));
  ASSERT_TRUE((concepts::logical_not.check<bool>()));
  ASSERT_TRUE((concepts::logical_not.check<int>()));
  ASSERT_TRUE((concepts::logical_not.check<decltype(!std::declval<int>())>()));
  ASSERT_FALSE((concepts::logical_not.check<no_operator_test>()));
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

TEST(Cpt_Utility, logical_and)
{
  ASSERT_TRUE((concepts::logical_and.check<logical_and_op_member_test, int>()));
  ASSERT_TRUE((concepts::logical_and.check<logical_and_op_friend_test, int>()));
  ASSERT_TRUE((concepts::logical_and.check<int, logical_and_op_friend_test>()));
  ASSERT_TRUE((concepts::logical_and.check<bool, int>()));
  ASSERT_TRUE((concepts::logical_and.check<double, int>()));
  ASSERT_TRUE((concepts::logical_and.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::logical_and.check<int, logical_and_op_member_test>()));
  ASSERT_FALSE((concepts::logical_and.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, logical_or)
{
  ASSERT_TRUE((concepts::logical_or.check<logical_or_op_member_test, int>()));
  ASSERT_TRUE((concepts::logical_or.check<logical_or_op_friend_test, int>()));
  ASSERT_TRUE((concepts::logical_or.check<int, logical_or_op_friend_test>()));
  ASSERT_TRUE((concepts::logical_or.check<bool, int>()));
  ASSERT_TRUE((concepts::logical_or.check<double, int>()));
  ASSERT_TRUE((concepts::logical_or.check<bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((concepts::logical_or.check<int, logical_or_op_member_test>()));
  ASSERT_FALSE((concepts::logical_or.check<no_operator_test, no_operator_test>()));
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

TEST(Cpt_Utility, comma)
{
  ASSERT_FALSE((concepts::comma.check<comma_restrict_test, int>()));
  ASSERT_TRUE((concepts::comma.check<comma_restrict_test, comma_restrict_test::rhs>()));
  ASSERT_TRUE((concepts::comma.check<no_operator_test, int>()));
}

TEST(Cpt_Utility, ternary)
{
  ASSERT_TRUE((concepts::ternary.check<bool, int, const double>()));
  ASSERT_TRUE((concepts::ternary.check<bool, const volatile int, float>()));
  ASSERT_TRUE((concepts::ternary.check<bool_convertible_test, int_convertible_test, double>()));
  ASSERT_FALSE((concepts::ternary.check<bool, no_operator_test, no_operator_test>()));
  ASSERT_FALSE((concepts::ternary.check<bool, no_operator_test, bool>()));
  ASSERT_FALSE((concepts::ternary.check<bool, std::map<int, double>, std::vector<int>>()));
  ASSERT_FALSE((concepts::ternary.check<bool_convertible_test, std::vector<float>, const float>()));
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

TEST(Cpt_Utility, invocable)
{
  static const auto a = 1.5;
  EXPECT_TRUE((concepts::invocable.check<decltype(invocable_test)>()));
  EXPECT_TRUE((concepts::invocable.check<decltype(invocable_int_test), int>()));
  EXPECT_TRUE((concepts::invocable.check<decltype(invocable_r_test)>()));
  EXPECT_TRUE((concepts::invocable.check<decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::invocable.check<invocable_functor_test, int, double>()));
  EXPECT_TRUE((concepts::invocable.check<invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::invocable
                 .check<decltype(&invocable_nested_functor_test::test), invocable_nested_functor_test, int, double>()));
  EXPECT_TRUE(
    (concepts::invocable
       .check<decltype(&invocable_nested_r_functor_test::test), invocable_nested_r_functor_test, int, double>()));
  EXPECT_FALSE((concepts::invocable.check<decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((concepts::invocable.check<decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((concepts::invocable.check<decltype(a)>()));
  EXPECT_FALSE((concepts::invocable.check<invocable_r_functor_test, std::vector<double>>()));
}

TEST(Cpt_Utility, invocable_r)
{
  EXPECT_TRUE((concepts::invocable_r.check<int, decltype(invocable_r_test)>()));
  EXPECT_TRUE((concepts::invocable_r.check<int, decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::invocable_r.check<double, decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((concepts::invocable_r.check<std::tuple<int, double>, invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::invocable_r.check<std::tuple<double, double>, invocable_r_functor_test, int, double>()));
  EXPECT_TRUE((concepts::invocable_r.check<std::tuple<double, double>, decltype(&invocable_nested_r_functor_test::test),
                                           invocable_nested_r_functor_test, int, double>()));
  EXPECT_FALSE((concepts::invocable_r.check<std::vector<double>, decltype(invocable_r_double_test), double>()));
  EXPECT_FALSE((concepts::invocable_r.check<int, invocable_functor_test, int, double>()));
}
