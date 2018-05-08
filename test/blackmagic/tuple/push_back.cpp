#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Push_back, Simple)
{
  ASSERT_TRUE(tuple::equals(tuple::push_back(std::make_tuple("str"sv, 1), 6.0), std::make_tuple("str"sv, 1, 6.0)));
}
