#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_Lockstep, Three)
{
  ASSERT_TRUE(functional::lockstep([](auto a, auto b, auto c) { return a + b + c; })(
                [](auto a) { return a + a; }, [](auto a) { return a * a; }, [](auto a) { return a - a / 2; })(1, 2, 4)
              == 8);
}
