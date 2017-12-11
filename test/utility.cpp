#include <concepts/concepts.hpp>

#include <gtest/gtest.h>

struct test_ {
  void* operator*()
  {
    return (void*) nullptr;
  }
};

TEST(Utility, is_dereferenceable)
{
  ASSERT_TRUE(concepts::dereferenceable<test_>);
  ASSERT_FALSE(traits::is_nothrow_dereferenceable_v<test_>);
}

void f()
{
}

TEST(Utility, is_invocable)
{
  static const auto a = 1.5;
  ASSERT_TRUE(concepts::invocable<decltype(f)>);
  ASSERT_FALSE(traits::is_invocable_v<decltype(a)>);
}