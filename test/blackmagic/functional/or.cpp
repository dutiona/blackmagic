#include <blackmagic/functional/functional.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;

TEST(Functional_Or, Simple)
{
  ASSERT_TRUE(functional::Or(true, false, true));
  ASSERT_FALSE(functional::Or(false, false, false));
}
