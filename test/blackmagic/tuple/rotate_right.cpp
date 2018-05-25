#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Rotate_right, Simple)
{
  ASSERT_TRUE(tuple::equal(tuple::rotate_right(std::make_tuple("str"sv, 6.0, 4)), std::make_tuple(4, "str"sv, 6.0)));
}
