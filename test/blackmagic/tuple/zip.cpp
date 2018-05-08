#include <blackmagic/tuple/tuple.hpp>

#include <string_view>

#include <gtest/gtest.h>

namespace tuple = blackmagic::tuple;
using namespace std::literals;

TEST(Tuple_Zip, Single)
{
  ASSERT_TRUE(tuple::equals(tuple::zip(std::make_tuple(1, 2, 3)),
                            std::make_tuple(std::make_tuple(1), std::make_tuple(2), std::make_tuple(3))));
}

TEST(Tuple_Zip, Empty)
{
  ASSERT_TRUE(tuple::equals(tuple::zip(), std::make_tuple()));
}

TEST(Tuple_Zip, EmptySingle)
{
  ASSERT_TRUE(tuple::equals(tuple::zip(std::make_tuple()), std::make_tuple(std::make_tuple())));
}

TEST(Tuple_Zip, EmptyMulti)
{
  ASSERT_TRUE(tuple::equals(tuple::zip(std::make_tuple(), std::make_tuple()),
                            std::make_tuple(std::make_tuple(), std::make_tuple())));
}

TEST(Tuple_Zip, Double)
{
  ASSERT_TRUE(
    tuple::equals(tuple::zip(std::make_tuple(1, 2, 3), std::make_tuple(1.0, 2.0, 3.0)),
                  std::make_tuple(std::make_tuple(1, 1.0), std::make_tuple(2, 2.0), std::make_tuple(3, 3.0))));
}

TEST(Tuple_Zip, Multi)
{
  ASSERT_TRUE(tuple::equals(
    tuple::zip(std::make_tuple(1, 2, 3), std::make_tuple(1.0, 2.0, 3.0), std::make_tuple("3.0"sv, "2.0"sv, "1.0"sv)),
    std::make_tuple(std::make_tuple(1, 1.0, "3.0"sv), std::make_tuple(2, 2.0, "2.0"sv),
                    std::make_tuple(3, 3.0, "1.0"sv))));
}

