#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_Compose, Two)
{
  ASSERT_TRUE(functional::compose([](auto a, auto b) { return a + b; }, [](auto a) { return a * a; })(5, 2) == 27);
}

TEST(Functional_Partial, Three)
{
  ASSERT_TRUE(functional::compose([](auto a, auto b, auto c) { return a - b + c; }, [](auto a) { return a * a; },
                                  [](auto a) { return a - a / 2; })(4, 6, 8)
              == 6);
}
