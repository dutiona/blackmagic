#include <metaprog/cpt/cpt.hpp>

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

TEST(Cpt_Iterator, always_true)
{
  ASSERT_TRUE(true);
}
