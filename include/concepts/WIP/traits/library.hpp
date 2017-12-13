#pragma once

#ifndef CONCEPTS_TRAITS_LIBRARY_HPP_
#define CONCEPTS_TRAITS_LIBRARY_HPP_

#include "utility.hpp"

#include <type_traits>
#include <utility>

namespace concepts { namespace details {

template <typename T, typename Arg1, typename Arg2>
using compare_equiv_t =
  decltype(!std::declval<T>()(std::declval<Arg1>(), std::declval<Arg2>())
           && !std::declval<T>()(std::declval<Arg2>(), std::declval<Arg1>())); // !cmp(a, b) && !cmp(b, a)


// Equality comparable

template <typename T, typename = void>
struct is_equality_comparable_impl : std::false_type {
};

template <typename T>
struct is_equality_comparable_impl<
  T, std::void_t<std::is_convertible_t<equality_t<T>, bool>, std::is_convertible_t<inequality_t<T>, bool>>>
  : std::true_type {
};

template <typename T>
using is_equality_comparable = is_equality_comparable_impl<T>;

template <typename T>
using is_equality_comparable_t = typename is_equality_comparable<T>::type;

template <typename T>
constexpr bool is_equality_comparable_v = is_equality_comparable<T>::value;


// Less than comparable

template <typename T, typename = void>
struct is_less_than_comparable_impl : std::false_type {
};

template <typename T>
struct is_less_than_comparable_impl<T, std::void_t<std::is_convertible_t<details::less_than_t<T>, bool>>>
  : std::true_type {
};

template <typename T>
using is_less_than_comparable = is_less_than_comparable_impl<T>;

template <typename T>
using is_less_than_comparable_t = typename is_less_than_comparable<T>::type;

template <typename T>
constexpr bool is_less_than_comparable_v = is_less_than_comparable<T>::value;


// ValueSwappable

template <typename T, typename U = T, typename = void>
struct is_value_swappable_impl : std::false_type {
};

template <typename T, typename U = T>
struct is_value_swappable_impl<
  T, U,
  std::void_t<traits::is_iterator_t<T>, traits::is_iterator_t<U>,
              std::is_swappable_with<traits::dereferenceable_t<T>, traits::dereferenceable_t<U>>::type>>
  : std::true_type {
};

template <typename T>
using is_value_swappable = is_value_swappable_impl<T>;

template <typename T>
using is_value_swappable_t = typename is_value_swappable_impl<T>::type;

template <typename T>
constexpr bool is_value_swappable_v = is_value_swappable_impl<T>::value;


}} // namespace concepts::details

#endif // CONCEPTS_TRAITS_LIBRARY_HPP_
