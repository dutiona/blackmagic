#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_Demux, Two)
{
  ASSERT_TRUE(functional::demux([](auto a, auto b) { return a * b; })([](auto a, auto b) { return a + b; },
                                                                      [](auto a, auto b) { return a - b; })(4, 2)
              == 12);
}
