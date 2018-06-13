#include <blackmagic/integral/integral.hpp>
#include <blackmagic/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple    = blackmagic::tuple;
namespace integral = blackmagic::integral;

TEST(Tuple_Unique, TrivialTypes)
{
  ASSERT_TRUE((tuple::equal(std::make_tuple(1, 2.0), tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55)))));
}

TEST(Tuple_Unique, Literals)
{
  using namespace integral::literals;
  ASSERT_TRUE(
    (tuple::equal(std::make_tuple(1_c, 2_c, 4_c), tuple::unique(std::make_tuple(1_c, 2_c, 4_c, 1_c, 2_c, 1_c)))));
}
