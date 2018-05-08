#include <blackmagic/common/common.hpp>
#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace common = blackmagic::common;
namespace tuple  = blackmagic::tuple;

TEST(Tuple_Copy_if, SimplePredicate)
{
  ASSERT_TRUE((tuple::equals(std::make_tuple(1, 3, 55),
                             tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_integral>))));
}

TEST(Tuple_Copy_if, ComplexPredicate)
{
  ASSERT_TRUE((tuple::equals(std::make_tuple(1, 3, 55),
                             tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_same, int>))));
}
