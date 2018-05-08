#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Reverse, Simple)
{
  ASSERT_TRUE(
    tuple::equals(std::make_tuple(0, 1, 4.0, 5.0, "str"sv), tuple::reverse(std::make_tuple("str"sv, 5.0, 4.0, 1, 0))));
}
