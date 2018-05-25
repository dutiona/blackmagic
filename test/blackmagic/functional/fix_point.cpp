#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_FixPoint, Fibonaci)
{
  ASSERT_TRUE(functional::fix_point([](auto self, auto n) {
                if (n == 0)
                  return 1;
                else
                  return n * self(n - 1);
              })(5)
              == 120);
}
