#pragma once

#ifndef CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_

#include <concepts/basic/traits.hpp>

#include <type_traits>

namespace concepts { namespace basic { namespace details {

namespace traits = traits::basic;

// default constructible
template <typename T, typename = void>
struct default_constructible_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the default constructible concept.");
};
template <typename T>
struct default_constructible_impl<
  T, std::enable_if_t<
       std::disjunction_v<traits::is_default_constructible_t<T>, traits::is_nothrow_default_constructible_t<T>,
                          traits::is_trivially_default_constructible_t<T>>>> : std::true_type {
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
  static_assert(sizeof(T) == -1, "T fails to model the move constructible concept.");
};
template <typename T>
struct move_constructible_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_move_constructible_t<T>, traits::is_nothrow_move_constructible_t<T>,
                                         traits::is_trivially_move_constructible_t<T>>>> : std::true_type {
};
template <typename T>
using move_constructible = move_constructible_impl<T>;
template <typename T>
using move_constructible_t = typename move_constructible<T>::type;
template <typename T>
constexpr bool move_constructible_v = move_constructible<T>::value;

// copy constructible
template <typename T, typename = void>
struct copy_constructible_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the copy constructible concept.");
};
template <typename T>
struct copy_constructible_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_copy_constructible_t<T>, traits::is_nothrow_copy_constructible_t<T>,
                                         traits::is_trivially_copy_constructible_t<T>>>> : std::true_type {
};
template <typename T>
using copy_constructible = copy_constructible_impl<T>;
template <typename T>
using copy_constructible_t = typename copy_constructible<T>::type;
template <typename T>
constexpr bool copy_constructible_v = copy_constructible<T>::value;

// move assignable
template <typename T, typename = void>
struct move_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the move assignable concept.");
};
template <typename T>
struct move_assignable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_move_assignable_t<T>, traits::is_nothrow_move_assignable_t<T>,
                                         traits::is_trivially_move_assignable_t<T>>>> : std::true_type {
};
template <typename T>
using move_assignable = move_assignable_impl<T>;
template <typename T>
using move_assignable_t = typename move_assignable<T>::type;
template <typename T>
constexpr bool move_assignable_v = move_assignable<T>::value;

// copy assignable
template <typename T, typename = void>
struct copy_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the copy assignable concept.");
};
template <typename T>
struct copy_assignable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_copy_assignable_t<T>, traits::is_nothrow_copy_assignable_t<T>,
                                         traits::is_trivially_copy_assignable_t<T>>>> : std::true_type {
};
template <typename T>
using copy_assignable = copy_assignable_impl<T>;
template <typename T>
using copy_assignable_t = typename copy_assignable<T>::type;
template <typename T>
constexpr bool copy_assignable_v = copy_assignable<T>::value;

// destructible
template <typename T, typename = void>
struct destructible_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the destructible concept.");
};
template <typename T>
struct destructible_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_destructible_t<T>, traits::is_nothrow_destructible_t<T>,
                                         traits::is_trivially_destructible_t<T>>>> : std::true_type {
};
template <typename T>
using destructible = destructible_impl<T>;
template <typename T>
using destructible_t = typename destructible<T>::type;
template <typename T>
constexpr bool destructible_v = destructible<T>::value;

}}} // namespace concepts::basic::details

#endif // CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
