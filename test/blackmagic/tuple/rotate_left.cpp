#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Rotate_left, Simple)
{
  ASSERT_TRUE(
    tuple::equals(tuple::rotate_left(std::make_tuple("str"sv, 6.0, 4)), std::make_tuple(6.0, 4, "str"sv)));
}
