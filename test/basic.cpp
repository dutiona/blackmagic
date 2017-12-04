#include "concepts/concepts.hpp"

#include <gtest/gtest.h>

struct default_constructible_test {
};

TEST(Basic, default_constructible)
{
  ASSERT_TRUE(concepts::DefaultConstructible<default_constructible_test>);
}