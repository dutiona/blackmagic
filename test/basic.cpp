#include <concepts/concepts.hpp>

#include <gtest/gtest.h>

struct default_constructible_test {
};

TEST(Basic, default_constructible)
{
  ASSERT_TRUE(concepts::default_constructible<default_constructible_test>);
}