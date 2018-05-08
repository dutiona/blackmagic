#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;

TEST(Tuple_Unpack, Tuple)
{
  ASSERT_TRUE(tuple::unpack(std::make_tuple(1, 2, 3, 4, 5), [](auto... x) { return (x + ...); }) == 15);
}

TEST(Tuple_Unpack, CArray)
{
  constexpr int t[] = {1, 2, 3, 4, 5};
  ASSERT_TRUE(tuple::unpack(t, [](auto... x) { return (x + ...); }) == 15);
}

TEST(Tuple_Unpack, StdArray)
{
  constexpr auto t = std::array<int, 5>{1, 2, 3, 4, 5};
  ASSERT_TRUE(tuple::unpack(t, [](auto... x) { return (x + ...); }) == 15);
}
