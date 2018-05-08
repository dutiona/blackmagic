#include <blackmagic/tuple/tuple.hpp>

#include <functional>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Sort, Simple)
{
  ASSERT_TRUE(tuple::equals(tuple::sort(std::less<>{}, std::make_tuple(20, 8, 15, 7, 3, 1, 1, 2, 8, 5, 4, 6)),
                            std::make_tuple(1, 1, 2, 3, 4, 5, 6, 7, 8, 8, 15, 20)));
}

TEST(Tuple_Sort, SimpleGreater)
{
  ASSERT_TRUE(tuple::equals(tuple::sort(std::greater<>{}, std::make_tuple(20, 8, 15, 7, 3, 1, 1, 2, 8, 5, 4, 6)),
                            std::make_tuple(20, 15, 8, 8, 7, 6, 5, 4, 3, 2, 1, 1)));
}
