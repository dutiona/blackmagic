#include <blackmagic/common/common.hpp>
#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace common = blackmagic::common;
namespace tuple  = blackmagic::tuple;

TEST(Tuple_Remove_if, SimplePredicate)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(2.0, 48.0),
                            tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_integral>))));
}

TEST(Tuple_Remove_if, ComplexPredicate)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(2.0, 48.0),
                            tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_same, int>))));
}
