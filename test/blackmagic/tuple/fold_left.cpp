#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;

TEST(Tuple_Fold_left, NoState)
{
  ASSERT_TRUE(tuple::fold_left(std::make_tuple(10, 2), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);
}

TEST(Tuple_Fold_left, WithState)
{
  ASSERT_TRUE(tuple::fold_left(std::make_tuple(2, 2, 1), [](auto lhs, auto rhs) { return lhs / rhs; }, 20) == 5);
}