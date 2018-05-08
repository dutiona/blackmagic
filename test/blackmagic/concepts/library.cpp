#include <blackmagic/concepts/concepts.hpp>

#include <gtest/gtest.h>

namespace concepts = blackmagic::concepts;

TEST(Cpt_Library, always_true)
{
  ASSERT_TRUE(true);
}
