#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

constexpr auto func_test(int a, int b, int c, int d)
{
  return a + b + c + d;
}

TEST(Functional_Partial, Function)
{
  ASSERT_TRUE(functional::partial(func_test, 1, 2)(4, 5) == 12);
}

TEST(Functional_Partial, Lambda)
{
  constexpr auto lmbd = [](int a, int b, long c, int d) { return a + b + c + d; };

  ASSERT_TRUE(functional::partial(lmbd, 1, 2)(4, 5) == 12);
}

struct functor {
  constexpr auto operator()(int a, int b, int c, int d) const
  {
    return func_test(a, b, c, d);
  }
};

TEST(Functional_Partial, FunctionObject)
{
  ASSERT_TRUE(functional::partial(functor{}, 1, 2)(4, 5) == 12);
}
