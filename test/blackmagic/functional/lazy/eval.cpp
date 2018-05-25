#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace lazy       = functional::lazy;

TEST(Functional_Lazy, Eval_Simple)
{
  int c = 0;
  ASSERT_TRUE(c == 0);

  ASSERT_TRUE(9
              == lazy::eval(lazy::make_lazy(
                   [&c](auto a, auto b) {
                     c++;
                     return a + b;
                   },
                   4, 5)));

  ASSERT_TRUE(c == 1);
}
