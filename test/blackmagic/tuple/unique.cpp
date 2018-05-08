#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;

TEST(Tuple_Unique, TrivialTypes)
{
  ASSERT_TRUE((tuple::equals(std::make_tuple(1, 2.0), tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55)))));
}
