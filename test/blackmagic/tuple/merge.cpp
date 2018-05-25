#include <blackmagic/tuple/tuple.hpp>

#include <functional>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Merge, Simple)
{
  ASSERT_TRUE(tuple::equal(tuple::merge(std::less<>{}, std::make_tuple(1, 5, 8)), std::make_tuple(1, 5, 8)));
}

TEST(Tuple_Merge, Double)
{
  ASSERT_TRUE(tuple::equal(tuple::merge(std::less<>{}, std::make_tuple(1, 5, 8), std::make_tuple(4, 5, 6, 7, 9)),
                           std::make_tuple(1, 4, 5, 5, 6, 7, 8, 9)));
}

TEST(Tuple_Merge, Triple)
{
  ASSERT_TRUE(tuple::equal(
    tuple::merge(std::less<>{}, std::make_tuple(0, 1, 5, 8), std::make_tuple(2, 6, 9), std::make_tuple(0, 3, 4, 7)),
    std::make_tuple(0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9)));
}

TEST(Tuple_Merge, DoubleGreater)
{
  ASSERT_TRUE(
    tuple::equal(tuple::merge(std::greater<>{}, std::make_tuple(8, 5, 1, 0), std::make_tuple(9, 7, 6, 5, 4, 3, 2)),
                 std::make_tuple(9, 8, 7, 6, 5, 5, 4, 3, 2, 1, 0)));
}
