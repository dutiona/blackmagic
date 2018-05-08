#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Back, Simple)
{
  ASSERT_TRUE(tuple::back(std::make_tuple(1, 6.0)) == 6.0);
}
