#include <metaprog/tuple/tuple.hpp>

#include <metaprog/tuple/print_all.hpp>

#include <functional>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;

TEST(Tuple_Merge, Simple)
{
  constexpr auto tpl = tuple::merge(std::less<>{}, std::make_tuple(1, 5, 8));
  tuple::print_all(tpl, std::cout);
  //ASSERT_TRUE(tuple::equals(tuple::merge(std::less<>{}, std::make_tuple(1, 5, 8)), std::make_tuple(1, 5, 8)));
}

/*
TEST(Tuple_Merge, Double)
{
  ASSERT_TRUE(tuple::equals(tuple::merge(std::less<>{}, std::make_tuple(1, 5, 8), std::make_tuple(4, 5, 6, 7, 9)),
                            std::make_tuple(1, 4, 5, 5, 6, 7, 8, 9)));
}
 */
