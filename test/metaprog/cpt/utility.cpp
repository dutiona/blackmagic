//#include <concepts/concepts.hpp>
#include "../../../include/metaprog/cpt/cpt.hpp"

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
  ASSERT_TRUE((cpt::check<concepts::indirection, indirection_test>()));
  ASSERT_TRUE((cpt::check<concepts::indirection, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::indirection, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::indirection, decltype(b)>()));
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
  EXPECT_TRUE((cpt::check<concepts::address_of, address_of_test>()));
  EXPECT_TRUE((cpt::check<concepts::address_of, decltype(*a)>()));
  EXPECT_TRUE((cpt::check<concepts::address_of, decltype(c)>()));
  EXPECT_FALSE((cpt::check<concepts::address_of, no_operator_test>()));
  EXPECT_FALSE((cpt::check<concepts::address_of, decltype(a)>()));
  EXPECT_FALSE((cpt::check<concepts::address_of, decltype(b)>()));
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
  ASSERT_TRUE((cpt::check<concepts::subscript, subscript_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::subscript, decltype(a), int>()));
  ASSERT_TRUE((cpt::check<concepts::subscript, decltype(b), int>()));
  ASSERT_TRUE((cpt::check<concepts::subscript, decltype(c), int>()));
  ASSERT_TRUE((cpt::check<concepts::subscript, decltype(e), int>()));
  ASSERT_TRUE((cpt::check<concepts::subscript, decltype(f), int>()));
  ASSERT_FALSE((cpt::check<concepts::subscript, decltype(d), int>()));
  ASSERT_FALSE((cpt::check<concepts::subscript, no_operator_test, int>()));
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
  ASSERT_TRUE((cpt::check<concepts::pointer_to_member_of_object, decltype(obj),
                          decltype(&pointer_to_member_of_object_test::a)>()));
  ASSERT_FALSE((cpt::check<concepts::pointer_to_member_of_object, decltype(obj),
                           decltype(&pointer_to_member_of_object_other_test::a)>()));
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
  ASSERT_TRUE((cpt::check<concepts::pointer_to_member_of_pointer, decltype(&obj),
                          decltype(&pointer_to_member_of_pointer_test::a)>()));
  ASSERT_FALSE((cpt::check<concepts::pointer_to_member_of_pointer, decltype(&obj),
                           decltype(&pointer_to_member_of_pointer_other_test::a)>()));
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
  ASSERT_TRUE((cpt::check<concepts::assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::assignable, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::assignable, no_operator_test>()));
  ASSERT_TRUE((cpt::check<concepts::assignable, assignable_rhs_test, assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::assignable, decltype(a), int>()));
  ASSERT_FALSE((cpt::check<concepts::assignable, decltype(b), no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::assignable, non_assignable_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, plus_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, plus_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::plus_assignable, plus_assignable_rhs_test, plus_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::plus_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::plus_assignable, decltype(b), plus_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus_assignable, plus_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::less_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::less_assignable, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::less_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::less_assignable, less_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::less_assignable, less_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_assignable, less_assignable_rhs_test, less_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::less_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::less_assignable, decltype(b), less_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_assignable, less_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, mult_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, mult_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::mult_assignable, mult_assignable_rhs_test, mult_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::mult_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::mult_assignable, decltype(b), mult_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::mult_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::mult_assignable, mult_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::div_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::div_assignable, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::div_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::div_assignable, div_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::div_assignable, div_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::div_assignable, div_assignable_rhs_test, div_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::div_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::div_assignable, decltype(b), div_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::div_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::div_assignable, div_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::mod_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::mod_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::mod_assignable, mod_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::mod_assignable, mod_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::mod_assignable, mod_assignable_rhs_test, mod_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::mod_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::mod_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::mod_assignable, decltype(b), mod_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::mod_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::mod_assignable, mod_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::and_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::and_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::and_assignable, and_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::and_assignable, and_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::and_assignable, and_assignable_rhs_test, and_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::and_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::and_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::and_assignable, decltype(b), and_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::and_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::and_assignable, and_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::or_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::or_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::or_assignable, or_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::or_assignable, or_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::or_assignable, or_assignable_rhs_test, or_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::or_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::or_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::or_assignable, decltype(b), or_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::or_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::or_assignable, or_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::xor_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::xor_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::xor_assignable, xor_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::xor_assignable, xor_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::xor_assignable, xor_assignable_rhs_test, xor_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::xor_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::xor_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::xor_assignable, decltype(b), xor_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::xor_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::xor_assignable, xor_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::lshift_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::lshift_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::lshift_assignable, lshift_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::lshift_assignable, lshift_assignable_rhs_test, lshift_assignable_rhs_test::rhs>()));
  ASSERT_TRUE((cpt::check<concepts::lshift_assignable, lshift_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::lshift_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::lshift_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::lshift_assignable, decltype(b), lshift_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::lshift_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::lshift_assignable, lshift_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::rshift_assignable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::rshift_assignable, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::rshift_assignable, rshift_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::rshift_assignable, rshift_assignable_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::rshift_assignable, rshift_assignable_rhs_test, rshift_assignable_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::rshift_assignable, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::rshift_assignable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::rshift_assignable, decltype(b), rshift_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::rshift_assignable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::rshift_assignable, rshift_assignable_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::positive, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::positive, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::positive, decltype(c)>()));
  ASSERT_TRUE((cpt::check<concepts::positive, positive_test>()));
  ASSERT_FALSE((cpt::check<concepts::positive, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::negative, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::negative, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::negative, decltype(c)>()));
  ASSERT_TRUE((cpt::check<concepts::negative, negative_test>()));
  ASSERT_FALSE((cpt::check<concepts::negative, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::Not, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::Not, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::Not, not_test>()));
  ASSERT_FALSE((cpt::check<concepts::Not, decltype(c)>()));
  ASSERT_FALSE((cpt::check<concepts::Not, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::plus, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::plus, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::plus, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::plus, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::plus, plus_test>()));
  ASSERT_TRUE((cpt::check<concepts::plus, plus_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::plus, plus_rhs_test, plus_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::plus, decltype(b), plus_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, plus_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::less, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::less, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::less, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::less, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::less, less_test>()));
  ASSERT_TRUE((cpt::check<concepts::less, less_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less, less_rhs_test, less_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::less, decltype(b), less_test>()));
  ASSERT_FALSE((cpt::check<concepts::less, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::less, less_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::mult, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::mult, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::mult, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::mult, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::mult, mult_test>()));
  ASSERT_TRUE((cpt::check<concepts::mult, mult_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::mult, mult_rhs_test, mult_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::mult, decltype(b), mult_test>()));
  ASSERT_FALSE((cpt::check<concepts::mult, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::mult, mult_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::div, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::div, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::div, decltype(b), double>()));
  ASSERT_TRUE((cpt::check<concepts::div, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::div, div_test>()));
  ASSERT_TRUE((cpt::check<concepts::div, div_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::div, div_rhs_test, div_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::div, decltype(b), div_test>()));
  ASSERT_FALSE((cpt::check<concepts::div, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::div, div_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::mod, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::mod, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::mod, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::mod, mod_test>()));
  ASSERT_TRUE((cpt::check<concepts::mod, mod_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::mod, mod_rhs_test, mod_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::mod, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::plus, decltype(b), mod_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, mod_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::And, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::And, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::And, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::And, and_test>()));
  ASSERT_TRUE((cpt::check<concepts::And, and_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::And, and_rhs_test, and_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::And, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::And, decltype(b), and_test>()));
  ASSERT_FALSE((cpt::check<concepts::And, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::And, and_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::Or, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::Or, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::Or, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::Or, or_test>()));
  ASSERT_TRUE((cpt::check<concepts::Or, or_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::Or, or_rhs_test, or_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::Or, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::Or, decltype(b), or_test>()));
  ASSERT_FALSE((cpt::check<concepts::Or, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::Or, or_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::Xor, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::Xor, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::Xor, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::Xor, xor_test>()));
  ASSERT_TRUE((cpt::check<concepts::Xor, xor_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::Xor, xor_rhs_test, xor_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::Xor, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::Xor, decltype(b), xor_test>()));
  ASSERT_FALSE((cpt::check<concepts::Xor, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::Xor, xor_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::lshift, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::lshift, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::lshift, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::lshift, lshift_test>()));
  ASSERT_TRUE((cpt::check<concepts::lshift, lshift_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::lshift, lshift_rhs_test, lshift_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::lshift, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::plus, decltype(b), lshift_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::plus, lshift_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::rshift, decltype(a)>()));
  ASSERT_TRUE((cpt::check<concepts::rshift, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::rshift, decltype(b), int_convertible_test>()));
  ASSERT_TRUE((cpt::check<concepts::rshift, rshift_test>()));
  ASSERT_TRUE((cpt::check<concepts::rshift, rshift_int_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::rshift, rshift_rhs_test, rshift_rhs_test::rhs>()));
  ASSERT_FALSE((cpt::check<concepts::rshift, decltype(b), double>()));
  ASSERT_FALSE((cpt::check<concepts::rshift, decltype(b), rshift_test>()));
  ASSERT_FALSE((cpt::check<concepts::rshift, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::rshift, rshift_int_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::pre_incrementable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::pre_incrementable, decltype(d)>()));
  ASSERT_TRUE((cpt::check<concepts::pre_incrementable, pre_incrementable_test>()));
  ASSERT_FALSE((cpt::check<concepts::pre_incrementable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_incrementable, decltype(c)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_incrementable, decltype(co)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_incrementable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::pre_incrementable, int_convertible_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::post_incrementable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::post_incrementable, decltype(d)>()));
  ASSERT_TRUE((cpt::check<concepts::post_incrementable, post_incrementable_test>()));
  ASSERT_FALSE((cpt::check<concepts::post_incrementable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::post_incrementable, decltype(c)>()));
  ASSERT_FALSE((cpt::check<concepts::post_incrementable, decltype(co)>()));
  ASSERT_FALSE((cpt::check<concepts::post_incrementable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::post_incrementable, int_convertible_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::pre_decrementable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::pre_decrementable, decltype(d)>()));
  ASSERT_TRUE((cpt::check<concepts::pre_decrementable, pre_decrementable_test>()));
  ASSERT_FALSE((cpt::check<concepts::pre_decrementable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_decrementable, decltype(c)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_decrementable, decltype(co)>()));
  ASSERT_FALSE((cpt::check<concepts::pre_decrementable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::pre_decrementable, int_convertible_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::post_decrementable, decltype(b)>()));
  ASSERT_TRUE((cpt::check<concepts::post_decrementable, decltype(d)>()));
  ASSERT_TRUE((cpt::check<concepts::post_decrementable, post_decrementable_test>()));
  ASSERT_FALSE((cpt::check<concepts::post_decrementable, decltype(a)>()));
  ASSERT_FALSE((cpt::check<concepts::post_decrementable, decltype(c)>()));
  ASSERT_FALSE((cpt::check<concepts::post_decrementable, decltype(co)>()));
  ASSERT_FALSE((cpt::check<concepts::post_decrementable, no_operator_test>()));
  ASSERT_FALSE((cpt::check<concepts::post_decrementable, int_convertible_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::equality, equality_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::equality, equality_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::equality, int, equality_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::equality, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::equality, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::equality, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::equality, int, equality_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::equality, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::inequality, inequality_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::inequality, inequality_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::inequality, int, inequality_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::inequality, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::inequality, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::inequality, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::inequality, int, inequality_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::inequality, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::less_than, less_than_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_than, less_than_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_than, int, less_than_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::less_than, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_than, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_than, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_than, int, less_than_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_than, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, less_equal_than_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, less_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, int, less_equal_than_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::less_equal_than, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_equal_than, int, less_equal_than_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::less_equal_than, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::greater_than, greater_than_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_than, greater_than_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_than, int, greater_than_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::greater_than, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_than, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_than, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::greater_than, int, greater_than_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::greater_than, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, greater_equal_than_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, greater_equal_than_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, int, greater_equal_than_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::greater_equal_than, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::greater_equal_than, int, greater_equal_than_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::greater_equal_than, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::logical_not, logical_not_test>()));
  ASSERT_TRUE((cpt::check<concepts::logical_not, bool>()));
  ASSERT_TRUE((cpt::check<concepts::logical_not, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_not, decltype(!std::declval<int>())>()));
  ASSERT_FALSE((cpt::check<concepts::logical_not, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::logical_and, logical_and_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_and, logical_and_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_and, int, logical_and_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::logical_and, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_and, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_and, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::logical_and, int, logical_and_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::logical_and, no_operator_test, no_operator_test>()));
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
  ASSERT_TRUE((cpt::check<concepts::logical_or, logical_or_op_member_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_or, logical_or_op_friend_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_or, int, logical_or_op_friend_test>()));
  ASSERT_TRUE((cpt::check<concepts::logical_or, bool, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_or, double, int>()));
  ASSERT_TRUE((cpt::check<concepts::logical_or, bool_convertible_test, int_convertible_test>()));
  ASSERT_FALSE((cpt::check<concepts::logical_or, int, logical_or_op_member_test>()));
  ASSERT_FALSE((cpt::check<concepts::logical_or, no_operator_test, no_operator_test>()));
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
  ASSERT_FALSE((cpt::check<concepts::comma, comma_restrict_test, int>()));
  ASSERT_TRUE((cpt::check<concepts::comma, comma_restrict_test, comma_restrict_test::rhs>) );
  ASSERT_TRUE((cpt::check<concepts::comma, no_operator_test, int>()));
}

TEST(Cpt_Utility, ternary)
{
  ASSERT_TRUE((cpt::check<concepts::ternary, bool, int, const double>()));
  ASSERT_TRUE((cpt::check<concepts::ternary, bool, const volatile int, float>()));
  ASSERT_TRUE((cpt::check<concepts::ternary, bool, no_operator_test, no_operator_test>()));
  ASSERT_TRUE((cpt::check<concepts::ternary, bool_convertible_test, int_convertible_test, double>()));
  ASSERT_FALSE((cpt::check<concepts::ternary, bool, no_operator_test, bool>()));
  ASSERT_FALSE((cpt::check<concepts::ternary, bool, std::map<int, double>, std::vector<int>>()));
  ASSERT_FALSE((cpt::check<concepts::ternary, bool_convertible_test, std::vector<float>, const float>()));
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

TEST(Cpt_Utility, invocable)
{
  static const auto a = 1.5;
  EXPECT_TRUE((cpt::check<concepts::invocable, decltype(invocable_test)>()));
  EXPECT_TRUE((cpt::check<concepts::invocable, decltype(invocable_int_test), int>()));
  EXPECT_TRUE((cpt::check<concepts::invocable, decltype(invocable_r_test)>()));
  EXPECT_TRUE((cpt::check<concepts::invocable_r, int, decltype(invocable_r_test)>()));
  EXPECT_TRUE((cpt::check<concepts::invocable, decltype(invocable_r_double_test), double>()));
  EXPECT_TRUE((cpt::check<concepts::invocable_r, int, decltype(invocable_r_double_test), double>()));
  EXPECT_FALSE((cpt::check<concepts::invocable, decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((cpt::check<concepts::invocable_r, double, decltype(invocable_r_double_test), double>()));
  EXPECT_FALSE((cpt::check<concepts::invocable, decltype(invocable_r_double_test)>()));
  EXPECT_FALSE((cpt::check<concepts::invocable, decltype(a)>()));
}
