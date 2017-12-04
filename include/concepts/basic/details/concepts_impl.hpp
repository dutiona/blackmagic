#pragma once

#ifndef CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_

#include <concepts/basic/traits.hpp>

#include <type_traits>

namespace concepts { namespace basic { namespace details {

// default constructible

template <typename T, typename = void>
struct default_constructible_impl : std::false_type {
  // TODO add explicit error message here via static assert
};

template <typename T>
struct default_constructible_impl<
  T, std::void_t<std::disjunction<concepts::basic::traits::is_default_constructible_v<T>,
                                  concepts::basic::traits::is_nothrow_default_constructible_v<T>,
                                  concepts::basic::traits::is_trivially_default_constructible_v<T>>::type>>
  : std::true_type {
};

template <typename T>
using default_constructible = default_constructible_impl<T>;

template <typename T>
using default_constructible_t = typename default_constructible<T>::type;

template <typename T>
constexpr bool default_constructible_v = default_constructible<T>::value;


// move constructible

template <typename T, typename = void>
struct move_constructible_impl : std::false_type {
  // TODO add explicit error message here via static assert
};

template <typename T>
struct move_constructible_impl<
  T, std::void_t<std::disjunction<concepts::basic::traits::is_move_constructible_v<T>,
                                  concepts::basic::traits::is_nothrow_move_constructible_v<T>,
                                  concepts::basic::traits::is_trivially_move_constructible_v<T>>::type>>
  : std::true_type {
};

template <typename T>
using move_constructible = move_constructible_impl<T>;

template <typename T>
using move_constructible_t = typename move_constructible<T>::type;

template <typename T>
constexpr bool move_constructible_v = move_constructible<T>::value;

}}} // namespace concepts::basic::details

#endif // CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_