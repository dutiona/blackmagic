#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Front, Simple)
{
  ASSERT_TRUE(tuple::front(std::make_tuple(1, 6.0)) == 1);
}
