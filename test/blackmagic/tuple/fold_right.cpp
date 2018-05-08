#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;

TEST(Tuple_Fold_right, NoState)
{
  ASSERT_TRUE(tuple::fold_right(std::make_tuple(2, 10), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);
}

TEST(Tuple_Fold_right, WithState)
{
  ASSERT_TRUE(tuple::fold_right(std::make_tuple(2, 2), [](auto lhs, auto rhs) { return lhs / rhs; }, 1, 20) == 5);
}
