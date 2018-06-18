#include <blackmagic/common/common.hpp>

#include <iostream>
#include <type_traits>
#include <typeinfo>

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
  static_assert(
    std::is_same_v<common::details::simple_common_reference_t<const int&, volatile double&>, const volatile double&>);
}

TEST(Common_CommonReference, TwoElements_BothRvalueReferences)
{
  static_assert(std::is_same_v<common::details::simple_common_reference_t<const int&&, double&&>, const double&>);
}

TEST(Common_CommonReference, TwoElements_Mixed_LhsLvalue)
{
  static_assert(std::is_same_v<common::details::simple_common_reference_t<const int&, double&&>, const double&>);
}

TEST(Common_CommonReference, TwoElements_Mixed_RhsLvalue)
{
  static_assert(std::is_same_v<common::details::simple_common_reference_t<const int&&, double&>, const double&>);
}
