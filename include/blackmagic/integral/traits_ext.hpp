#pragma once

#include "types.hpp"

#include "../common/traits_ext.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <typename T>
using is_integral_constant_c = common::is_typed_valued_instantiation_of<std::integral_constant, T>;
template <typename T>
inline constexpr const auto is_integral_constant_c_v = _v<is_integral_constant_c<T>>;

template <typename T, typename U>
using is_specialized_integral_constant_c =
  common::is_specialized_typed_valued_instantiation_of<std::integral_constant, T, U>;
template <typename T, typename U>
inline constexpr const auto is_specialized_integral_constant_c_v = _v<is_specialized_integral_constant_c<T, U>>;

namespace {

template <template <auto...> class T, typename U, typename V>
using is_type = std::disjunction<common::is_valued_instantiation_of<T, V>,
                                 std::conjunction<is_integral_constant_c<V>, std::is_same<decltype(V()), U>>>;
}

template <typename T>
using is_bool_c = is_type<bool_t, bool, T>;
template <typename T>
inline constexpr const auto is_bool_c_v = _v<is_bool_c<T>>;

template <typename T>
using is_char_c = is_type<char_t, char, T>;
template <typename T>
inline constexpr const auto is_char_c_v = _v<is_char_c<T>>;

template <typename T>
using is_short_c = is_type<short_t, short, T>;
template <typename T>
inline constexpr const auto is_short_c_v = _v<is_short_c<T>>;

template <typename T>
using is_int_c = is_type<int_t, int, T>;
template <typename T>
inline constexpr const auto is_int_c_v = _v<is_int_c<T>>;

template <typename T>
using is_long_c = is_type<long_t, long, T>;
template <typename T>
inline constexpr const auto is_long_c_v = _v<is_long_c<T>>;

template <typename T>
using is_long_long_c = is_type<long_long_t, long long, T>;
template <typename T>
inline constexpr const auto is_long_long_c_v = _v<is_long_long_c<T>>;

template <typename T>
using is_unsigned_char_c = is_type<unsigned_char_t, unsigned char, T>;
template <typename T>
inline constexpr const auto is_unsigned_char_c_v = _v<is_unsigned_char_c<T>>;

template <typename T>
using is_unsigned_short_c = is_type<unsigned_short_t, unsigned short, T>;
template <typename T>
inline constexpr const auto is_unsigned_short_c_v = _v<is_unsigned_short_c<T>>;

template <typename T>
using is_unsigned_c = is_type<unsigned_t, unsigned, T>;
template <typename T>
inline constexpr const auto is_unsigned_c_v = _v<is_unsigned_c<T>>;

template <typename T>
using is_unsigned_int_c = is_type<unsigned_int_t, unsigned int, T>;
template <typename T>
inline constexpr const auto is_unsigned_int_c_v = _v<is_unsigned_int_c<T>>;

template <typename T>
using is_unsigned_long_c = is_type<unsigned_long_t, unsigned long, T>;
template <typename T>
inline constexpr const auto is_unsigned_long_c_v = _v<is_unsigned_long_c<T>>;

template <typename T>
using is_unsigned_long_long_c = is_type<unsigned_long_long_t, unsigned long long, T>;
template <typename T>
inline constexpr const auto is_unsigned_long_long_c_v = _v<is_unsigned_long_long_c<T>>;

template <typename T>
using is_size_t_c = is_type<size_t_t, size_t, T>;
template <typename T>
inline constexpr const auto is_size_t_c_v = _v<is_size_t_c<T>>;

} // namespace blackmagic::integral
