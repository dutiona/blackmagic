#include <metaprog/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;
using namespace std::literals;

TEST(Tuple_Rotate_right, Simple)
{
  ASSERT_TRUE(tuple::equals(tuple::rotate_right(std::make_tuple("str"sv, 6.0, 4)), std::make_tuple(4, "str"sv, 6.0)));
}
