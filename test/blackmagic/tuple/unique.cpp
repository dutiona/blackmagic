#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Unique, TrivialTypes)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(1, 2.0), tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55)))));
}
