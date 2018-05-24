#pragma once

#include "types.hpp"

#include "../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using blackmagic::common::_v;

template <typename T>
using is_bool_c = std::is_same<typename T::value_type, bool>;
template <typename T>
inline constexpr const auto is_bool_c_v = _v<is_bool_c<T>>;

template <typename T>
using is_char_c = std::is_same<typename T::value_type, char>;
template <typename T>
inline constexpr const auto is_char_c_v = _v<is_char_c<T>>;

template <typename T>
using is_short_c = std::is_same<typename T::value_type, short>;
template <typename T>
inline constexpr const auto is_short_c_v = _v<is_short_c<T>>;

template <typename T>
using is_int_c = std::is_same<typename T::value_type, int>;
template <typename T>
inline constexpr const auto is_int_c_v = _v<is_int_c<T>>;

template <typename T>
using is_long_c = std::is_same<typename T::value_type, long>;
template <typename T>
inline constexpr const auto is_long_c_v = _v<is_long_c<T>>;

template <typename T>
using is_long_long_c = std::is_same<typename T::value_type, long long>;
template <typename T>
inline constexpr const auto is_long_long_c_v = _v<is_long_long_c<T>>;

template <typename T>
using is_unsigned_char_c = std::is_same<typename T::value_type, unsigned char>;
template <typename T>
inline constexpr const auto is_unsigned_char_c_v = _v<is_unsigned_char_c<T>>;

template <typename T>
using is_unsigned_short_c = std::is_same<typename T::value_type, unsigned short>;
template <typename T>
inline constexpr const auto is_unsigned_short_c_v = _v<is_unsigned_short_c<T>>;

template <typename T>
using is_unsigned_c = std::is_same<typename T::value_type, unsigned>;
template <typename T>
inline constexpr const auto is_unsigned_c_v = _v<is_unsigned_c<T>>;

template <typename T>
using is_unsigned_int_c = std::is_same<typename T::value_type, unsigned int>;
template <typename T>
inline constexpr const auto is_unsigned_int_c_v = _v<is_unsigned_int_c<T>>;

template <typename T>
using is_unsigned_long_c = std::is_same<typename T::value_type, unsigned long>;
template <typename T>
inline constexpr const auto is_unsigned_long_c_v = _v<is_unsigned_long_c<T>>;

template <typename T>
using is_unsigned_long_long_c = std::is_same<typename T::value_type, unsigned long long>;
template <typename T>
inline constexpr const auto is_unsigned_long_long_c_v = _v<is_unsigned_long_long_c<T>>;

template <typename T>
using is_size_t_c = std::is_same<typename T::value_type, size_t>;
template <typename T>
inline constexpr const auto is_size_t_c_v = _v<is_size_t_c<T>>;

} // namespace blackmagic::integral
