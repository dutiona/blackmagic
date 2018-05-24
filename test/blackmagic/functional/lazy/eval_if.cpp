#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace lazy       = functional::lazy;

TEST(Functional_Lazy, Eval_If_Simple)
{
  int c = 0;

  ASSERT_TRUE(c == 0);
  ASSERT_TRUE(9
              == lazy::eval_if(true,
                               lazy::make_lazy(
                                 [&c](auto a, auto b) {
                                   c++;
                                   return a + b;
                                 },
                                 4, 5),
                               lazy::make_lazy(
                                 [&c](auto a, auto b) {
                                   c--;
                                   return b - a;
                                 },
                                 4, 5)));

  ASSERT_TRUE(c == 1);

  ASSERT_TRUE(1
              == lazy::eval_if(false,
                               lazy::make_lazy(
                                 [&c](auto a, auto b) {
                                   c++;
                                   return a + b;
                                 },
                                 4, 5),
                               lazy::make_lazy(
                                 [&c](auto a, auto b) {
                                   c--;
                                   return b - a;
                                 },
                                 4, 5)));
  ASSERT_TRUE(c == 0);
}
