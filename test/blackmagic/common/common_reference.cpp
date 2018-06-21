#include <blackmagic/common/common.hpp>

#include <type_traits>

#include <gtest/gtest.h>


namespace common = blackmagic::common;

template <typename T>
using has_type = typename T::type;

TEST(Common_CommonReference, EmptyList)
{
  static_assert(!common::is_detected_v<has_type, common::common_reference<>>);
}

TEST(Common_CommonReference, OneElement)
{
  static_assert(std::is_same_v<int, common::common_reference_t<int>>);
}

TEST(Common_CommonReference, TwoElements_BothLvalueReferences)
{
  static_assert(std::is_same_v<common::common_reference_t<const int&, volatile double&>, const volatile double&>);
}

TEST(Common_CommonReference, TwoElements_BothRvalueReferences)
{
  static_assert(std::is_same_v<common::common_reference_t<const int&&, double&&>, const double&>);
}

TEST(Common_CommonReference, TwoElements_Mixed_LhsLvalue)
{
  //static_assert(std::is_same_v<common::common_reference_t<const int&, double&&>, const double&>);
}

TEST(Common_CommonReference, TwoElements_Mixed_RhsLvalue)
{
  //static_assert(std::is_same_v<common::common_reference_t<const int&&, double&>, const double&>);
}

struct A {
};
struct B {
};

template <typename T, typename U, typename = void>
struct has_common_reference : std::false_type {
};
template <typename T, typename U>
struct has_common_reference<T, U, std::void_t<common::common_reference_t<T, U>>> : std::true_type {
};

template <typename T, typename U>
inline constexpr auto has_common_reference_v = has_common_reference<T, U>::value;

TEST(Common_CommonReference, TwoElements_Different)
{
  static_assert(!common::details::impl_::valid_cond_expr_v_<A, B>);
  static_assert(has_common_reference_v<A, B>);
}
