#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Pop_front, Simple)
{
  ASSERT_TRUE(tuple::equal(tuple::pop_front(std::make_tuple("str"sv, 1, 6.0)), std::make_tuple(1, 6.0)));
}
