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

// pod
template <typename T, typename = void>
struct pod_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the POD concept.");
};
template <typename T>
struct pod_impl<T, std::enable_if_t<traits::is_pod_v<T>>> : std::true_type {
};
template <typename T>
using pod = pod_impl<T>;
template <typename T>
using pod_t = typename pod<T>::type;
template <typename T>
constexpr bool pod_v = pod<T>::value;

}}} // namespace concepts::layout::details

#endif // CONCEPTS_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
