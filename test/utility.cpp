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
  // ASSERT_TRUE(concepts::dereferenceable<test_>);
  // ASSERT_FALSE(traits::is_nothrow_dereferenceable_v<test_>);
}
