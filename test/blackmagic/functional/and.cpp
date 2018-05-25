#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_And, Simple)
{
  ASSERT_TRUE(functional::And(true, true, true));
  ASSERT_FALSE(functional::And(true, false, true));
}
