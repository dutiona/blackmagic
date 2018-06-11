#pragma once

#include "types.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::integral {

using common::_v;

namespace {

template <typename T, typename U, typename = void>
struct is_integral_type : std::false_type {
};

template <template <typename, auto> class T, typename U, typename L, auto V>
struct is_integral_type<T<L, V>, U, std::enable_if_t<std::is_same_v<std::integral_constant<U, V>, T<L, V>>>>
  : std::true_type {
};

} // namespace

template <typename T>
using is_bool_c = is_integral_type<T, bool>;
template <typename T>
inline constexpr const auto is_bool_c_v = _v<is_bool_c<T>>;

template <typename T>
using is_char_c = is_integral_type<T, char>;
template <typename T>
inline constexpr const auto is_char_c_v = _v<is_char_c<T>>;

template <typename T>
using is_short_c = is_integral_type<T, short>;
template <typename T>
inline constexpr const auto is_short_c_v = _v<is_short_c<T>>;

template <typename T>
using is_int_c = is_integral_type<T, int>;
template <typename T>
inline constexpr const auto is_int_c_v = _v<is_int_c<T>>;

template <typename T>
using is_long_c = is_integral_type<T, long>;
template <typename T>
inline constexpr const auto is_long_c_v = _v<is_long_c<T>>;

template <typename T, typename = void>
using is_long_long_c = is_integral_type<T, long long>;
template <typename T>
inline constexpr const auto is_long_long_c_v = _v<is_long_long_c<T>>;

template <typename T>
using is_unsigned_char_c = is_integral_type<T, unsigned char>;
template <typename T>
inline constexpr const auto is_unsigned_char_c_v = _v<is_unsigned_char_c<T>>;

template <typename T>
using is_unsigned_short_c = is_integral_type<T, unsigned short>;
template <typename T>
inline constexpr const auto is_unsigned_short_c_v = _v<is_unsigned_short_c<T>>;

template <typename T>
using is_unsigned_c = is_integral_type<T, unsigned>;
template <typename T>
inline constexpr const auto is_unsigned_c_v = _v<is_unsigned_c<T>>;

template <typename T>
using is_unsigned_int_c = is_integral_type<T, unsigned int>;
template <typename T>
inline constexpr const auto is_unsigned_int_c_v = _v<is_unsigned_int_c<T>>;

template <typename T>
using is_unsigned_long_c = is_integral_type<T, unsigned long>;
template <typename T>
inline constexpr const auto is_unsigned_long_c_v = _v<is_unsigned_long_c<T>>;

template <typename T>
using is_unsigned_long_long_c = is_integral_type<T, unsigned long long>;
template <typename T>
inline constexpr const auto is_unsigned_long_long_c_v = _v<is_unsigned_long_long_c<T>>;

template <typename T>
using is_size_t_c = is_integral_type<T, size_t>;
template <typename T>
inline constexpr const auto is_size_t_c_v = _v<is_size_t_c<T>>;

} // namespace blackmagic::integral
