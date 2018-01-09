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
  ASSERT_TRUE((cpt::check<indirection_test>(concepts::indirection)));
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::indirection)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::indirection)));
  ASSERT_FALSE((cpt::check<decltype(b)>(concepts::indirection)));
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
  ASSERT_TRUE((cpt::check<address_of_test>(concepts::address_of)));
  ASSERT_TRUE((cpt::check<decltype(*a)>(concepts::address_of)));
  ASSERT_TRUE((cpt::check<decltype(c)>(concepts::address_of)));
#ifndef _MSC_VER // TODO/FIXME remove when reported bug is fixed
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::address_of)));
#endif
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::address_of)));
  ASSERT_FALSE((cpt::check<decltype(b)>(concepts::address_of)));
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
  ASSERT_TRUE((cpt::check<subscript_test, int>(concepts::subscript)));
  ASSERT_TRUE((cpt::check<decltype(a), int>(concepts::subscript)));
  ASSERT_TRUE((cpt::check<decltype(b), int>(concepts::subscript)));
  ASSERT_TRUE((cpt::check<decltype(c), int>(concepts::subscript)));
  ASSERT_TRUE((cpt::check<decltype(e), int>(concepts::subscript)));
  ASSERT_TRUE((cpt::check<decltype(f), int>(concepts::subscript)));
  ASSERT_FALSE((cpt::check<decltype(d), int>(concepts::subscript)));
  ASSERT_FALSE((cpt::check<no_operator_test, int>(concepts::subscript)));
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
    (cpt::check<decltype(obj), decltype(&pointer_to_member_of_object_test::a)>(concepts::pointer_to_member_of_object)));
  ASSERT_FALSE((cpt::check<decltype(obj), decltype(&pointer_to_member_of_object_other_test::a)>(
    concepts::pointer_to_member_of_object)));
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
  ASSERT_TRUE((cpt::check<decltype(&obj), decltype(&pointer_to_member_of_pointer_test::a)>(
    concepts::pointer_to_member_of_pointer)));
  ASSERT_FALSE((cpt::check<decltype(&obj), decltype(&pointer_to_member_of_pointer_other_test::a)>(
    concepts::pointer_to_member_of_pointer)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::assignable)));
  ASSERT_TRUE((cpt::check<no_operator_test>(concepts::assignable)));
  ASSERT_TRUE((cpt::check<assignable_rhs_test, assignable_rhs_test::rhs>(concepts::assignable)));
  ASSERT_FALSE((cpt::check<decltype(a), int>(concepts::assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), no_operator_test>(concepts::assignable)));
  ASSERT_FALSE((cpt::check<non_assignable_test>(concepts::assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::plus_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::plus_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::plus_assignable)));
  ASSERT_TRUE((cpt::check<plus_assignable_test>(concepts::plus_assignable)));
  ASSERT_TRUE((cpt::check<plus_assignable_int_test, int>(concepts::plus_assignable)));
  ASSERT_TRUE((cpt::check<plus_assignable_rhs_test, plus_assignable_rhs_test::rhs>(concepts::plus_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::plus_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), plus_assignable_test>(concepts::plus_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::plus_assignable)));
  ASSERT_FALSE((cpt::check<plus_assignable_int_test>(concepts::plus_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::less_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::less_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::less_assignable)));
  ASSERT_TRUE((cpt::check<less_assignable_test>(concepts::less_assignable)));
  ASSERT_TRUE((cpt::check<less_assignable_int_test, int>(concepts::less_assignable)));
  ASSERT_TRUE((cpt::check<less_assignable_rhs_test, less_assignable_rhs_test::rhs>(concepts::less_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::less_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), less_assignable_test>(concepts::less_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::less_assignable)));
  ASSERT_FALSE((cpt::check<less_assignable_int_test>(concepts::less_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::mult_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::mult_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::mult_assignable)));
  ASSERT_TRUE((cpt::check<mult_assignable_test>(concepts::mult_assignable)));
  ASSERT_TRUE((cpt::check<mult_assignable_int_test, int>(concepts::mult_assignable)));
  ASSERT_TRUE((cpt::check<mult_assignable_rhs_test, mult_assignable_rhs_test::rhs>(concepts::mult_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::mult_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), mult_assignable_test>(concepts::mult_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::mult_assignable)));
  ASSERT_FALSE((cpt::check<mult_assignable_int_test>(concepts::mult_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::div_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::div_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::div_assignable)));
  ASSERT_TRUE((cpt::check<div_assignable_test>(concepts::div_assignable)));
  ASSERT_TRUE((cpt::check<div_assignable_int_test, int>(concepts::div_assignable)));
  ASSERT_TRUE((cpt::check<div_assignable_rhs_test, div_assignable_rhs_test::rhs>(concepts::div_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::div_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), div_assignable_test>(concepts::div_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::div_assignable)));
  ASSERT_FALSE((cpt::check<div_assignable_int_test>(concepts::div_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::mod_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::mod_assignable)));
  ASSERT_TRUE((cpt::check<mod_assignable_test>(concepts::mod_assignable)));
  ASSERT_TRUE((cpt::check<mod_assignable_int_test, int>(concepts::mod_assignable)));
  ASSERT_TRUE((cpt::check<mod_assignable_rhs_test, mod_assignable_rhs_test::rhs>(concepts::mod_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::mod_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::mod_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), mod_assignable_test>(concepts::mod_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::mod_assignable)));
  ASSERT_FALSE((cpt::check<mod_assignable_int_test>(concepts::mod_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::and_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::and_assignable)));
  ASSERT_TRUE((cpt::check<and_assignable_test>(concepts::and_assignable)));
  ASSERT_TRUE((cpt::check<and_assignable_int_test, int>(concepts::and_assignable)));
  ASSERT_TRUE((cpt::check<and_assignable_rhs_test, and_assignable_rhs_test::rhs>(concepts::and_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::and_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::and_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), and_assignable_test>(concepts::and_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::and_assignable)));
  ASSERT_FALSE((cpt::check<and_assignable_int_test>(concepts::and_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::or_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::or_assignable)));
  ASSERT_TRUE((cpt::check<or_assignable_test>(concepts::or_assignable)));
  ASSERT_TRUE((cpt::check<or_assignable_int_test, int>(concepts::or_assignable)));
  ASSERT_TRUE((cpt::check<or_assignable_rhs_test, or_assignable_rhs_test::rhs>(concepts::or_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::or_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::or_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), or_assignable_test>(concepts::or_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::or_assignable)));
  ASSERT_FALSE((cpt::check<or_assignable_int_test>(concepts::or_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::xor_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::xor_assignable)));
  ASSERT_TRUE((cpt::check<xor_assignable_test>(concepts::xor_assignable)));
  ASSERT_TRUE((cpt::check<xor_assignable_int_test, int>(concepts::xor_assignable)));
  ASSERT_TRUE((cpt::check<xor_assignable_rhs_test, xor_assignable_rhs_test::rhs>(concepts::xor_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::xor_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::xor_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), xor_assignable_test>(concepts::xor_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::xor_assignable)));
  ASSERT_FALSE((cpt::check<xor_assignable_int_test>(concepts::xor_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::lshift_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::lshift_assignable)));
  ASSERT_TRUE((cpt::check<lshift_assignable_int_test, int>(concepts::lshift_assignable)));
  ASSERT_TRUE((cpt::check<lshift_assignable_rhs_test, lshift_assignable_rhs_test::rhs>(concepts::lshift_assignable)));
  ASSERT_TRUE((cpt::check<lshift_assignable_test>(concepts::lshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::lshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::lshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), lshift_assignable_test>(concepts::lshift_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::lshift_assignable)));
  ASSERT_FALSE((cpt::check<lshift_assignable_int_test>(concepts::lshift_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::rshift_assignable)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::rshift_assignable)));
  ASSERT_TRUE((cpt::check<rshift_assignable_test>(concepts::rshift_assignable)));
  ASSERT_TRUE((cpt::check<rshift_assignable_int_test, int>(concepts::rshift_assignable)));
  ASSERT_TRUE((cpt::check<rshift_assignable_rhs_test, rshift_assignable_rhs_test::rhs>(concepts::rshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::rshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::rshift_assignable)));
  ASSERT_FALSE((cpt::check<decltype(b), rshift_assignable_test>(concepts::rshift_assignable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::rshift_assignable)));
  ASSERT_FALSE((cpt::check<rshift_assignable_int_test>(concepts::rshift_assignable)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::positive)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::positive)));
  ASSERT_TRUE((cpt::check<decltype(c)>(concepts::positive)));
  ASSERT_TRUE((cpt::check<positive_test>(concepts::positive)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::positive)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::negative)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::negative)));
  ASSERT_TRUE((cpt::check<decltype(c)>(concepts::negative)));
  ASSERT_TRUE((cpt::check<negative_test>(concepts::negative)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::negative)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::Not)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::Not)));
  ASSERT_TRUE((cpt::check<not_test>(concepts::Not)));
  ASSERT_FALSE((cpt::check<decltype(c)>(concepts::Not)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::Not)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::plus)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::plus)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::plus)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::plus)));
  ASSERT_TRUE((cpt::check<plus_test>(concepts::plus)));
  ASSERT_TRUE((cpt::check<plus_int_test, int>(concepts::plus)));
  ASSERT_TRUE((cpt::check<plus_rhs_test, plus_rhs_test::rhs>(concepts::plus)));
  ASSERT_FALSE((cpt::check<decltype(b), plus_test>(concepts::plus)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::plus)));
  ASSERT_FALSE((cpt::check<plus_int_test>(concepts::plus)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::less)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::less)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::less)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::less)));
  ASSERT_TRUE((cpt::check<less_test>(concepts::less)));
  ASSERT_TRUE((cpt::check<less_int_test, int>(concepts::less)));
  ASSERT_TRUE((cpt::check<less_rhs_test, less_rhs_test::rhs>(concepts::less)));
  ASSERT_FALSE((cpt::check<decltype(b), less_test>(concepts::less)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::less)));
  ASSERT_FALSE((cpt::check<less_int_test>(concepts::less)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::mult)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::mult)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::mult)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::mult)));
  ASSERT_TRUE((cpt::check<mult_test>(concepts::mult)));
  ASSERT_TRUE((cpt::check<mult_int_test, int>(concepts::mult)));
  ASSERT_TRUE((cpt::check<mult_rhs_test, mult_rhs_test::rhs>(concepts::mult)));
  ASSERT_FALSE((cpt::check<decltype(b), mult_test>(concepts::mult)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::mult)));
  ASSERT_FALSE((cpt::check<mult_int_test>(concepts::mult)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::div)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::div)));
  ASSERT_TRUE((cpt::check<decltype(b), double>(concepts::div)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::div)));
  ASSERT_TRUE((cpt::check<div_test>(concepts::div)));
  ASSERT_TRUE((cpt::check<div_int_test, int>(concepts::div)));
  ASSERT_TRUE((cpt::check<div_rhs_test, div_rhs_test::rhs>(concepts::div)));
  ASSERT_FALSE((cpt::check<decltype(b), div_test>(concepts::div)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::div)));
  ASSERT_FALSE((cpt::check<div_int_test>(concepts::div)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::mod)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::mod)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::mod)));
  ASSERT_TRUE((cpt::check<mod_test>(concepts::mod)));
  ASSERT_TRUE((cpt::check<mod_int_test, int>(concepts::mod)));
  ASSERT_TRUE((cpt::check<mod_rhs_test, mod_rhs_test::rhs>(concepts::mod)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::mod)));
  ASSERT_FALSE((cpt::check<decltype(b), mod_test>(concepts::mod)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::mod)));
  ASSERT_FALSE((cpt::check<mod_int_test>(concepts::mod)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::And)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::And)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::And)));
  ASSERT_TRUE((cpt::check<and_test>(concepts::And)));
  ASSERT_TRUE((cpt::check<and_int_test, int>(concepts::And)));
  ASSERT_TRUE((cpt::check<and_rhs_test, and_rhs_test::rhs>(concepts::And)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::And)));
  ASSERT_FALSE((cpt::check<decltype(b), and_test>(concepts::And)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::And)));
  ASSERT_FALSE((cpt::check<and_int_test>(concepts::And)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::Or)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::Or)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::Or)));
  ASSERT_TRUE((cpt::check<or_test>(concepts::Or)));
  ASSERT_TRUE((cpt::check<or_int_test, int>(concepts::Or)));
  ASSERT_TRUE((cpt::check<or_rhs_test, or_rhs_test::rhs>(concepts::Or)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::Or)));
  ASSERT_FALSE((cpt::check<decltype(b), or_test>(concepts::Or)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::Or)));
  ASSERT_FALSE((cpt::check<or_int_test>(concepts::Or)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::Xor)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::Xor)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::Xor)));
  ASSERT_TRUE((cpt::check<xor_test>(concepts::Xor)));
  ASSERT_TRUE((cpt::check<xor_int_test, int>(concepts::Xor)));
  ASSERT_TRUE((cpt::check<xor_rhs_test, xor_rhs_test::rhs>(concepts::Xor)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::Xor)));
  ASSERT_FALSE((cpt::check<decltype(b), xor_test>(concepts::Xor)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::Xor)));
  ASSERT_FALSE((cpt::check<xor_int_test>(concepts::Xor)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::lshift)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::lshift)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::lshift)));
  ASSERT_TRUE((cpt::check<lshift_test>(concepts::lshift)));
  ASSERT_TRUE((cpt::check<lshift_int_test, int>(concepts::lshift)));
  ASSERT_TRUE((cpt::check<lshift_rhs_test, lshift_rhs_test::rhs>(concepts::lshift)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::lshift)));
  ASSERT_FALSE((cpt::check<decltype(b), lshift_test>(concepts::lshift)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::lshift)));
  ASSERT_FALSE((cpt::check<lshift_int_test>(concepts::lshift)));
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
  ASSERT_TRUE((cpt::check<decltype(a)>(concepts::rshift)));
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::rshift)));
  ASSERT_TRUE((cpt::check<decltype(b), int_convertible_test>(concepts::rshift)));
  ASSERT_TRUE((cpt::check<rshift_test>(concepts::rshift)));
  ASSERT_TRUE((cpt::check<rshift_int_test, int>(concepts::rshift)));
  ASSERT_TRUE((cpt::check<rshift_rhs_test, rshift_rhs_test::rhs>(concepts::rshift)));
  ASSERT_FALSE((cpt::check<decltype(b), double>(concepts::rshift)));
  ASSERT_FALSE((cpt::check<decltype(b), rshift_test>(concepts::rshift)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::rshift)));
  ASSERT_FALSE((cpt::check<rshift_int_test>(concepts::rshift)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::pre_incrementable)));
  ASSERT_TRUE((cpt::check<decltype(d)>(concepts::pre_incrementable)));
  ASSERT_TRUE((cpt::check<pre_incrementable_test>(concepts::pre_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::pre_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(c)>(concepts::pre_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(co)>(concepts::pre_incrementable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::pre_incrementable)));
  ASSERT_FALSE((cpt::check<int_convertible_test>(concepts::pre_incrementable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::post_incrementable)));
  ASSERT_TRUE((cpt::check<decltype(d)>(concepts::post_incrementable)));
  ASSERT_TRUE((cpt::check<post_incrementable_test>(concepts::post_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::post_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(c)>(concepts::post_incrementable)));
  ASSERT_FALSE((cpt::check<decltype(co)>(concepts::post_incrementable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::post_incrementable)));
  ASSERT_FALSE((cpt::check<int_convertible_test>(concepts::post_incrementable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::pre_decrementable)));
  ASSERT_TRUE((cpt::check<decltype(d)>(concepts::pre_decrementable)));
  ASSERT_TRUE((cpt::check<pre_decrementable_test>(concepts::pre_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::pre_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(c)>(concepts::pre_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(co)>(concepts::pre_decrementable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::pre_decrementable)));
  ASSERT_FALSE((cpt::check<int_convertible_test>(concepts::pre_decrementable)));
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
  ASSERT_TRUE((cpt::check<decltype(b)>(concepts::post_decrementable)));
  ASSERT_TRUE((cpt::check<decltype(d)>(concepts::post_decrementable)));
  ASSERT_TRUE((cpt::check<post_decrementable_test>(concepts::post_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(a)>(concepts::post_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(c)>(concepts::post_decrementable)));
  ASSERT_FALSE((cpt::check<decltype(co)>(concepts::post_decrementable)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::post_decrementable)));
  ASSERT_FALSE((cpt::check<int_convertible_test>(concepts::post_decrementable)));
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
  ASSERT_TRUE((cpt::check<equality_op_member_test, int>(concepts::equality)));
  ASSERT_TRUE((cpt::check<equality_op_friend_test, int>(concepts::equality)));
  ASSERT_TRUE((cpt::check<int, equality_op_friend_test>(concepts::equality)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::equality)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::equality)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::equality)));
  ASSERT_FALSE((cpt::check<int, equality_op_member_test>(concepts::equality)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::equality)));
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
  ASSERT_TRUE((cpt::check<inequality_op_member_test, int>(concepts::inequality)));
  ASSERT_TRUE((cpt::check<inequality_op_friend_test, int>(concepts::inequality)));
  ASSERT_TRUE((cpt::check<int, inequality_op_friend_test>(concepts::inequality)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::inequality)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::inequality)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::inequality)));
  ASSERT_FALSE((cpt::check<int, inequality_op_member_test>(concepts::inequality)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::inequality)));
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
  ASSERT_TRUE((cpt::check<less_than_op_member_test, int>(concepts::less_than)));
  ASSERT_TRUE((cpt::check<less_than_op_friend_test, int>(concepts::less_than)));
  ASSERT_TRUE((cpt::check<int, less_than_op_friend_test>(concepts::less_than)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::less_than)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::less_than)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::less_than)));
  ASSERT_FALSE((cpt::check<int, less_than_op_member_test>(concepts::less_than)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::less_than)));
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
  ASSERT_TRUE((cpt::check<less_equal_than_op_member_test, int>(concepts::less_equal_than)));
  ASSERT_TRUE((cpt::check<less_equal_than_op_friend_test, int>(concepts::less_equal_than)));
  ASSERT_TRUE((cpt::check<int, less_equal_than_op_friend_test>(concepts::less_equal_than)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::less_equal_than)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::less_equal_than)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::less_equal_than)));
  ASSERT_FALSE((cpt::check<int, less_equal_than_op_member_test>(concepts::less_equal_than)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::less_equal_than)));
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
  ASSERT_TRUE((cpt::check<greater_than_op_member_test, int>(concepts::greater_than)));
  ASSERT_TRUE((cpt::check<greater_than_op_friend_test, int>(concepts::greater_than)));
  ASSERT_TRUE((cpt::check<int, greater_than_op_friend_test>(concepts::greater_than)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::greater_than)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::greater_than)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::greater_than)));
  ASSERT_FALSE((cpt::check<int, greater_than_op_member_test>(concepts::greater_than)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::greater_than)));
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
  ASSERT_TRUE((cpt::check<greater_equal_than_op_member_test, int>(concepts::greater_equal_than)));
  ASSERT_TRUE((cpt::check<greater_equal_than_op_friend_test, int>(concepts::greater_equal_than)));
  ASSERT_TRUE((cpt::check<int, greater_equal_than_op_friend_test>(concepts::greater_equal_than)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::greater_equal_than)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::greater_equal_than)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::greater_equal_than)));
  ASSERT_FALSE((cpt::check<int, greater_equal_than_op_member_test>(concepts::greater_equal_than)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::greater_equal_than)));
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
  ASSERT_TRUE((cpt::check<logical_not_test>(concepts::logical_not)));
  ASSERT_TRUE((cpt::check<bool>(concepts::logical_not)));
  ASSERT_TRUE((cpt::check<int>(concepts::logical_not)));
  ASSERT_TRUE((cpt::check<decltype(!std::declval<int>())>(concepts::logical_not)));
  ASSERT_FALSE((cpt::check<no_operator_test>(concepts::logical_not)));
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
  ASSERT_TRUE((cpt::check<logical_and_op_member_test, int>(concepts::logical_and)));
  ASSERT_TRUE((cpt::check<logical_and_op_friend_test, int>(concepts::logical_and)));
  ASSERT_TRUE((cpt::check<int, logical_and_op_friend_test>(concepts::logical_and)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::logical_and)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::logical_and)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::logical_and)));
  ASSERT_FALSE((cpt::check<int, logical_and_op_member_test>(concepts::logical_and)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::logical_and)));
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
  ASSERT_TRUE((cpt::check<logical_or_op_member_test, int>(concepts::logical_or)));
  ASSERT_TRUE((cpt::check<logical_or_op_friend_test, int>(concepts::logical_or)));
  ASSERT_TRUE((cpt::check<int, logical_or_op_friend_test>(concepts::logical_or)));
  ASSERT_TRUE((cpt::check<bool, int>(concepts::logical_or)));
  ASSERT_TRUE((cpt::check<double, int>(concepts::logical_or)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test>(concepts::logical_or)));
  ASSERT_FALSE((cpt::check<int, logical_or_op_member_test>(concepts::logical_or)));
  ASSERT_FALSE((cpt::check<no_operator_test, no_operator_test>(concepts::logical_or)));
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
  comma_restrict_test{}, comma_restrict_test::rhs{};
  ASSERT_FALSE((cpt::check<comma_restrict_test, int>(concepts::comma)));
  ASSERT_TRUE((cpt::check<comma_restrict_test, comma_restrict_test::rhs>(concepts::comma)));
  ASSERT_TRUE((cpt::check<no_operator_test, int>(concepts::comma)));
}

TEST(Cpt_Utility, ternary)
{
  ASSERT_TRUE((cpt::check<bool, int, const double>(concepts::ternary)));
  ASSERT_TRUE((cpt::check<bool, const volatile int, float>(concepts::ternary)));
  ASSERT_TRUE((cpt::check<bool_convertible_test, int_convertible_test, double>(concepts::ternary)));
  ASSERT_FALSE((cpt::check<bool, no_operator_test, no_operator_test>(concepts::ternary)));
  ASSERT_FALSE((cpt::check<bool, no_operator_test, bool>(concepts::ternary)));
  ASSERT_FALSE((cpt::check<bool, std::map<int, double>, std::vector<int>>(concepts::ternary)));
  ASSERT_FALSE((cpt::check<bool_convertible_test, std::vector<float>, const float>(concepts::ternary)));
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
  EXPECT_TRUE((cpt::check<decltype(invocable_test)>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<decltype(invocable_int_test), int>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<decltype(invocable_r_test)>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<int, decltype(invocable_r_test)>(concepts::invocable_r)));
  EXPECT_TRUE((cpt::check<decltype(invocable_r_double_test), double>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<int, decltype(invocable_r_double_test), double>(concepts::invocable_r)));
  EXPECT_TRUE((cpt::check<double, decltype(invocable_r_double_test), double>(concepts::invocable_r)));
  EXPECT_TRUE((cpt::check<invocable_functor_test, int, double>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<invocable_r_functor_test, int, double>(concepts::invocable)));
  EXPECT_TRUE((cpt::check<std::tuple<int, double>, invocable_r_functor_test, int, double>(concepts::invocable_r)));
  EXPECT_TRUE((cpt::check<std::tuple<double, double>, invocable_r_functor_test, int, double>(concepts::invocable_r)));
  EXPECT_TRUE((cpt::check<decltype(&invocable_nested_functor_test::test), invocable_nested_functor_test, int, double>(
    concepts::invocable)));
  EXPECT_TRUE(
    (cpt::check<decltype(&invocable_nested_r_functor_test::test), invocable_nested_r_functor_test, int, double>(
      concepts::invocable)));
  EXPECT_TRUE((cpt::check<std::tuple<double, double>, decltype(&invocable_nested_r_functor_test::test),
                          invocable_nested_r_functor_test, int, double>(concepts::invocable_r)));
  EXPECT_FALSE((cpt::check<std::vector<double>, decltype(invocable_r_double_test), double>(concepts::invocable_r)));
  EXPECT_FALSE((cpt::check<decltype(invocable_r_double_test)>(concepts::invocable)));
  EXPECT_FALSE((cpt::check<decltype(invocable_r_double_test)>(concepts::invocable)));
  EXPECT_FALSE((cpt::check<decltype(a)>(concepts::invocable)));
  EXPECT_FALSE((cpt::check<invocable_r_functor_test, std::vector<double>>(concepts::invocable)));
  EXPECT_FALSE((cpt::check<int, invocable_functor_test, int, double>(concepts::invocable_r)));
}
