#include <type_traits>
#include <utility>

#include <gtest/gtest.h>

template <typename T>
using _is_dereferenceable_expr = decltype(*std::declval<T>());
template <typename T>
constexpr bool _is_dereferenceable_expr_nothrow_v = noexcept(*std::declval<T>());

// is_dereferenceable
template <typename T, typename = void>
struct is_dereferenceable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_dereferenceable_impl<T, std::void_t<_is_dereferenceable_expr<T>>> : std::true_type {
};
// is_nothrow_dereferenceable
template <typename T, typename Valid = void, typename Noexcept = void>
struct is_nothrow_dereferenceable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};

template <typename T, typename Valid>
struct is_nothrow_dereferenceable_impl<T, Valid, std::enable_if_t<_is_dereferenceable_expr_nothrow_v<T>>>
  : is_dereferenceable_impl<T, Valid> {
};


struct test_ {
  void* operator*()
  {
    return (void*) nullptr;
  }
};

TEST(Utility, is_dereferenceable)
{
  ASSERT_TRUE(is_dereferenceable_impl<test_>::value);
  ASSERT_FALSE(is_nothrow_dereferenceable_impl<test_>::value);
}