#include <metaprog/tuple/tuple.hpp>

#include <gtest/gtest.h>

namespace tuple = metaprog::tuple;

TEST(Tuple_Back, Simple)
{
  ASSERT_TRUE(tuple::back(std::make_tuple(1, 6.0)) == 6.0);
}
