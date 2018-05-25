#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Push_front, Simple)
{
  ASSERT_TRUE(tuple::equal(tuple::push_front(std::make_tuple("str"sv, 1), 6.0), std::make_tuple(6.0, "str"sv, 1)));
}
