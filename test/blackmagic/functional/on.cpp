#include <blackmagic/functional/functional.hpp>
#include <blackmagic/pair/pair.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace pair       = blackmagic::pair;

TEST(Functional_On, PlusPair)
{
  ASSERT_TRUE(functional::on([](auto a, auto b, auto c) { return a + b + c; },
                             pair::first)(std::make_pair(1, 2.0), std::make_pair(2, 4.0), std::make_pair(3, 8.0))
              == 6);

  ASSERT_TRUE(functional::on([](auto a, auto b, auto c) { return a + b + c; },
                             pair::second)(std::make_pair(1, 2.0), std::make_pair(2, 4.0), std::make_pair(3, 8.0))
              == 14.0);
}
