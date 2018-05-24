#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_Not, Simple)
{
  ASSERT_TRUE(functional::Not(false));
  ASSERT_FALSE(functional::Not(true));
}
