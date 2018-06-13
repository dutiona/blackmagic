#include <blackmagic/common/common.hpp>
#include <blackmagic/integral/integral.hpp>
#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace common   = blackmagic::common;
namespace tuple    = blackmagic::tuple;
namespace integral = blackmagic::integral;

TEST(Tuple_Copy_if, SimplePredicate)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(1, 3, 55),
                            tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_integral>))));
}

TEST(Tuple_Copy_if, ComplexPredicate)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(1, 3, 55),
                            tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55), common::trait<std::is_same, int>))));
}

TEST(Tuple_Remove_if, IntegralPredicate)
{
  using namespace integral::literals;
  ASSERT_TRUE(
    (tuple::equal(std::make_tuple(1_c, 1_c), tuple::copy_if(std::make_tuple(1_c, 2_c, 1_c), integral::equal.to(1_c)))));
}
