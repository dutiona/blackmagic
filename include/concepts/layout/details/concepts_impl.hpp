#pragma once

#ifndef CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_

#include <concepts/layout/traits.hpp>

#include <type_traits>

namespace concepts { namespace layout { namespace details {

namespace traits = traits::layout;

// trivially copyable
template <typename T, typename = void>
struct trivially_copyable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the trivially copyable concept.");
};
template <typename T>
struct trivially_copyable_impl<T, std::enable_if_t<traits::is_trivially_copyable_v<T>>> : std::true_type {
};
template <typename T>
using trivially_copyable = trivially_copyable_impl<T>;
template <typename T>
using trivially_copyable_t = typename trivially_copyable<T>::type;
template <typename T>
constexpr bool trivially_copyable_v = trivially_copyable<T>::value;

// trivial
template <typename T, typename = void>
struct trivial_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the trivial concept.");
};
template <typename T>
struct trivial_impl<T, std::enable_if_t<traits::is_trivial_v<T>>> : std::true_type {
};
template <typename T>
using trivial = trivial_impl<T>;
template <typename T>
using trivial_t = typename trivial<T>::type;
template <typename T>
constexpr bool trivial_v = trivial<T>::value;

// standard layout
template <typename T, typename = void>
struct standard_layout_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the standard layout concept.");
};
template <typename T>
struct standard_layout_impl<T, std::enable_if_t<traits::is_standard_layout_v<T>>> : std::true_type {
};
template <typename T>
using standard_layout = standard_layout_impl<T>;
template <typename T>
using standard_layout_t = typename standard_layout<T>::type;
template <typename T>
constexpr bool standard_layout_v = standard_layout<T>::value;

}}} // namespace concepts::layout::details

#endif // CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
