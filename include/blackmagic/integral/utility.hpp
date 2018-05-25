#pragma once

#include "types.hpp"

#include "../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace utility {

using common::_v;
using common::_v_t;


inline namespace arithmetic {
template <typename T>
using increment_t = std::integral_constant<decltype(_v_t<T> + 1), (_v_t<T> + 1)>;
template <typename T>
inline constexpr const auto increment_v = _v<increment_t<T>>;

template <typename T>
using decrement_t = std::integral_constant<decltype(_v_t<T> - 1), (_v_t<T> - 1)>;
template <typename T>
inline constexpr const auto decrement_v = _v<decrement_t<T>>;

template <typename T, typename U>
using plus_t = std::integral_constant<decltype(_v_t<T> + _v_t<U>), (_v_t<T> + _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto plus_v = _v<plus_t<T, U>>;

template <typename T, typename U>
using minus_t = std::integral_constant<decltype(_v_t<T> - _v_t<U>), (_v_t<T> - _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto minus_v = _v<minus_t<T, U>>;

template <typename T, typename U>
using mult_t = std::integral_constant<decltype(_v_t<T> * _v_t<U>), (_v_t<T> * _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto mult_v = _v<mult_t<T, U>>;

template <typename T, typename U>
using div_t = std::integral_constant<decltype(_v_t<T> / _v_t<U>), (_v_t<T> / _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto div_v = _v<div_t<T, U>>;

template <typename T, typename U>
using mod_t = std::integral_constant<decltype(_v_t<T> % _v_t<U>), _v_t<T> % _v_t<U>>;
template <typename T, typename U>
inline constexpr const auto mod_v = _v<mod_t<T, U>>;

template <typename T>
using positive_t = std::integral_constant<decltype(+_v_t<T>), (+_v_t<T>)>;
template <typename T>
inline constexpr const auto positive_v = _v<positive_t<T>>;

template <typename T>
using negative_t = std::integral_constant<decltype(-_v_t<T>), (-_v_t<T>)>;
template <typename T>
inline constexpr const auto negative_v = _v<negative_t<T>>;

template <typename T>
using bit_not_t = std::integral_constant<decltype(~_v_t<T>), (~_v_t<T>)>;
template <typename T>
inline constexpr const auto bit_not_v = _v<bit_not_t<T>>;

template <typename T, typename U>
using bit_and_t = std::integral_constant<decltype(_v_t<T> & _v_t<U>), (_v_t<T> & _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_and_v = _v<bit_and_t<T, U>>;

template <typename T, typename U>
using bit_or_t = std::integral_constant<decltype(_v_t<T> | _v_t<U>), (_v_t<T> | _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_or_v = _v<bit_or_t<T, U>>;

template <typename T, typename U>
using bit_xor_t = std::integral_constant<decltype(_v_t<T> ^ _v_t<U>), (_v_t<T> ^ _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_xor_v = _v<bit_xor_t<T, U>>;

template <typename T, typename U>
using bit_lshift_t = std::integral_constant<decltype(_v_t<T> << _v_t<U>), (_v_t<T> << _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_lshift_v = _v<bit_lshift_t<T, U>>;

template <typename T, typename U>
// clang-format off
using bit_rshift_t = std::integral_constant<decltype(_v_t<T> >> _v_t<U>), (_v_t<T> >> _v_t<U>)>;
// clang-format on
template <typename T, typename U>
inline constexpr const auto bit_rshift_v = _v<bit_rshift_t<T, U>>;

} // namespace arithmetic


inline namespace comparison {
template <typename T, typename U>
using equal_t = bool_t<(_v_t<T> == _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto equal_v = _v<equal_t<T, U>>;

template <typename T, typename U>
using not_equal_t = bool_t<(_v_t<T> != _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto not_equal_v = _v<not_equal_t<T, U>>;

template <typename T, typename U>
// clang-format off
using greater_t = bool_t<(_v_t<T> > _v_t<U>)>;
// clang-format on
template <typename T, typename U>
inline constexpr const auto greater_v = _v<greater_t<T, U>>;

template <typename T, typename U>
using less_t = bool_t<(_v_t<T> < _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto less_v = _v<less_t<T, U>>;

template <typename T, typename U>
using greater_equal_t = bool_t<(_v_t<T> >= _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto greater_equal_v = _v<greater_equal_t<T, U>>;

template <typename T, typename U>
using less_equal_t = bool_t<(_v_t<T> <= _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto less_equal_v = _v<less_equal_t<T, U>>;

} // namespace comparison


inline namespace logical {
template <typename T, typename U>
using logical_and_t = bool_t<(_v_t<T> && _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto logical_and_v = _v<logical_and_t<T, U>>;

template <typename T, typename U>
using logical_or_t = bool_t<(_v_t<T> || _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto logical_or_v = _v<logical_or_t<T, U>>;

template <typename T>
using logical_not_t = bool_t<(!_v_t<T>)>;
template <typename T>
inline constexpr const auto logical_not_v = _v<logical_not_t<T>>;

} // namespace logical

}} // namespace blackmagic::integral::utility
