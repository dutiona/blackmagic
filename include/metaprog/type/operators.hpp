#pragma once

#include "integral_types.hpp"

#include <type_traits>

namespace metaprog::type {


template <typename T>
using increment = std::integral_constant<decltype(T::type::value + 1), T::type::value + 1>;

template <typename T>
using decrement = std::integral_constant<decltype(T::type::value - 1), T::type::value - 1>;

template <typename T, typename U>
using plus = std::integral_constant<decltype(T::type::value + U::type::value), T::type::value + U::type::value>;

template <typename T, typename U>
using minus = std::integral_constant<decltype(T::type::value - U::type::value), T::type::value - U::type::value>;

template <typename T, typename U>
using multiplies = std::integral_constant<decltype(T::type::value * U::type::value), T::type::value * U::type::value>;

template <typename T, typename U>
using divides = std::integral_constant<decltype(T::type::value / U::type::value), T::type::value / U::type::value>;

template <typename T>
using negate = std::integral_constant<decltype(-T::type::value), -T::type::value>;

template <typename T, typename U>
using modulus = std::integral_constant<decltype(T::type::value % U::type::value), T::type::value % U::type::value>;

template <typename T, typename U>
using equal_to = bool_<T::type::value == U::type::value>;

template <typename T, typename U>
using not_equal_to = bool_<T::type::value != U::type::value>;

template <typename T, typename U>
using greater = bool_<(T::type::value > U::type::value)>;

template <typename T, typename U>
using less = bool_<(T::type::value < U::type::value)>;

template <typename T, typename U>
using greater_equal = bool_<(T::type::value >= U::type::value)>;

template <typename T, typename U>
using less_equal = bool_<(T::type::value <= U::type::value)>;

template <typename T, typename U>
using bit_and = std::integral_constant<decltype(T::type::value & U::type::value), T::type::value & U::type::value>;

template <typename T, typename U>
using bit_or = std::integral_constant<decltype(T::type::value | U::type::value), T::type::value | U::type::value>;

template <typename T, typename U>
using bit_xor = std::integral_constant<decltype(T::type::value ^ U::type::value), T::type::value ^ U::type::value>;

template <typename T>
using bit_not = std::integral_constant<decltype(~T::type::value), ~T::type::value>;

} // namespace metaprog::type
