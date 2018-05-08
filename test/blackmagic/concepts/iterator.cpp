#include <blackmagic/concepts/concepts.hpp>

#include <gtest/gtest.h>

namespace concepts = blackmagic::concepts;

TEST(Cpt_Iterator, always_true)
{
  ASSERT_TRUE(true);
}
