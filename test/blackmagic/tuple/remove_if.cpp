#include <blackmagic/common/common.hpp>
#include <blackmagic/integral/integral.hpp>
#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace common   = blackmagic::common;
namespace tuple    = blackmagic::tuple;
namespace integral = blackmagic::integral;

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

TEST(Tuple_Remove_if, IntegralPredicate)
{
  using namespace integral::literals;
  ASSERT_TRUE(
    (tuple::equal(std::make_tuple(2_c), tuple::remove_if(std::make_tuple(1_c, 2_c, 1_c), integral::equal.to(1_c)))));
}
