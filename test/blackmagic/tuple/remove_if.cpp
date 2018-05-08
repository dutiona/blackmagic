#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple          = blackmagic::tuple;
namespace common_helpers = blackmagic::common::helpers;

TEST(Tuple_Remove_if, SimplePredicate)
{
  ASSERT_TRUE((tuple::equals(std::make_tuple(2.0, 48.0), tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                          common_helpers::trait<std::is_integral>))));
}

TEST(Tuple_Remove_if, ComplexPredicate)
{
  ASSERT_TRUE((tuple::equals(std::make_tuple(2.0, 48.0), tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                          common_helpers::trait<std::is_same, int>))));
}
