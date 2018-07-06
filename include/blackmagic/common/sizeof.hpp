#pragma once

#include <type_traits>

namespace blackmagic::common { inline namespace size_of {

template <typename T>
struct size_of {
  static constexpr std::size_t value = sizeof(T);
};

template <typename T, typename U>
using sizeof_equal = std::bool_constant<(sizeof(T) == sizeof(U))>;

template <typename T, typename U>
using sizeof_not_equal = std::bool_constant<(sizeof(T) != sizeof(U))>;

template <typename T, typename U>
using sizeof_less = std::bool_constant<(sizeof(T) < sizeof(U))>;

template <typename T, typename U>
using sizeof_less_equal = std::bool_constant<(sizeof(T) <= sizeof(U))>;

template <typename T, typename U>
using sizeof_greater = std::bool_constant<(sizeof(T) > sizeof(U))>;

template <typename T, typename U>
using sizeof_greater_equal = std::bool_constant<(sizeof(T) >= sizeof(U))>;

}} // namespace blackmagic::common::size_of
