#include <metaprog/concepts/concepts.hpp>

#include <gtest/gtest.h>

namespace concepts = metaprog::concepts;

TEST(Cpt_Library, always_true)
{
  ASSERT_TRUE(true);
}
