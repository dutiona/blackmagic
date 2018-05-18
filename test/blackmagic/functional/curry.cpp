#include <blackmagic/functional/functional.hpp>
#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace integral   = blackmagic::integral;

constexpr auto func_test(int a, int b, int c, int d)
{
  return a + b + c + d;
}

TEST(Functional_Curry, Function)
{
  ASSERT_TRUE(functional::curry(func_test, integral::size_t_t<4>{})(1, 2)(4)(5) == 12);
}

TEST(Functional_Curry, Lambda)
{
  constexpr auto lmbd = [](int a, int b, long c, int d) { return a + b + c + d; };

  ASSERT_TRUE(functional::curry(lmbd, integral::size_t_t<4>{})(1, 2)(4)(5) == 12);
}

struct functor {
  constexpr auto operator()(int a, int b, int c, int d) const
  {
    return func_test(a, b, c, d);
  }
};

TEST(Functional_Curry, FunctionObject)
{
  ASSERT_TRUE(functional::curry(functor{}, integral::size_t_t<4>{})(1, 2)(4)(5) == 12);
}
