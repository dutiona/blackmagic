#pragma once

#ifndef CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_

//#include <concepts/layout/traits.hpp>
#include "../traits.hpp"

#include <type_traits>

namespace concepts { namespace layout { namespace details {

namespace traits = traits::layout;

// trivially copyable
template <bool SilentFailure, typename T, typename = void>
struct trivially_copyable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the trivially_copyable concept.");
};
template <bool SilentFailure, typename T>
struct trivially_copyable_impl<SilentFailure, T, std::enable_if_t<traits::is_trivially_copyable_v<T>>>
  : std::true_type {
};

// trivial
template <bool SilentFailure, typename T, typename = void>
struct trivial_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the trivial concept.");
};
template <bool SilentFailure, typename T>
struct trivial_impl<SilentFailure, T, std::enable_if_t<traits::is_trivial_v<T>>> : std::true_type {
};

// standard layout
template <bool SilentFailure, typename T, typename = void>
struct standard_layout_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the standard_layout concept.");
};
template <bool SilentFailure, typename T>
struct standard_layout_impl<SilentFailure, T, std::enable_if_t<traits::is_standard_layout_v<T>>> : std::true_type {
};

}}} // namespace concepts::layout::details

#endif // CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
