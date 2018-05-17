#pragma once

#include "types.hpp"

#include "../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace utility {

namespace common = blackmagic::common;
using common::_v;
using common::_v_t;

template <typename T>
using increment_t = std::integral_constant<decltype(_v_t<T> + 1), (_v_t<T> + 1)>;
template <typename T>
inline constexpr const auto increment_v = _v<increment_t<T>>;

template <typename T>
using decrement_t = std::integral_constant<decltype(_v_t<T> - 1), (_v_t<T> - 1)>;
template <typename T>
inline constexpr const auto decrement_v = _v<decrement_t<T>>;

template <typename T, typename U>
using binary_plus_t = std::integral_constant<decltype(_v_t<T> + _v_t<U>), (_v_t<T> + _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto binary_plus_v = _v<binary_plus_t<T, U>>;

template <typename T, typename U>
using binary_minus_t = std::integral_constant<decltype(_v_t<T> - _v_t<U>), (_v_t<T> - _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto binary_minus_v = _v<binary_minus_t<T, U>>;

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
using unary_plus_t = std::integral_constant<decltype(+_v_t<T>), (+_v_t<T>)>;
template <typename T>
inline constexpr const auto unary_plus_v = _v<unary_plus_t<T>>;

template <typename T>
using unary_minus_t = std::integral_constant<decltype(-_v_t<T>), (-_v_t<T>)>;
template <typename T>
inline constexpr const common::trait_t<unary_minus_t, T> unary_minus{};

template <typename T, typename U>
using equal_to_t = bool_t<(_v_t<T> == _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto equal_to_v = _v<equal_to_t<T, U>>;

template <typename T, typename U>
using not_equal_to_t = bool_t<(_v_t<T> != _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto not_equal_to_v = _v<not_equal_to_t<T, U>>;

template <typename T, typename U>
using greater_t = bool_t<(_v_t<T>> _v_t<U>)>;
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

template <typename T>
using bit_not_t = std::integral_constant<decltype(~_v_t<T>), (~_v_t<T>)>;
template <typename T>
inline constexpr const auto bit_not_v = _v<bit_not_t<T>>;


inline namespace traits {
template <typename T>
inline constexpr const common::trait_t<increment_t, T> increment{};

template <typename T>
inline constexpr const common::trait_t<decrement_t, T> decrement{};

template <typename T, typename U>
inline constexpr const common::trait_t<binary_plus_t, T, U> binary_plus{};

template <typename T, typename U>
inline constexpr const common::trait_t<binary_minus_t, T, U> binary_minus{};

template <typename T, typename U>
inline constexpr const common::trait_t<mult_t, T, U> mult{};

template <typename T, typename U>
inline constexpr const common::trait_t<div_t, T, U> div{};

template <typename T, typename U>
inline constexpr const common::trait_t<mod_t, T, U> mod{};

template <typename T>
inline constexpr const common::trait_t<unary_plus_t, T> unary_plus{};

template <typename T>
inline constexpr const common::trait_t<unary_minus_t, T> unary_minus{};

template <typename T, typename U>
inline constexpr const common::trait_t<equal_to_t, T, U> equal_to{};

template <typename T, typename U>
inline constexpr const common::trait_t<not_equal_to_t, T, U> not_equal_to{};

template <typename T, typename U>
inline constexpr const common::trait_t<greater_t, T, U> greater{};

template <typename T, typename U>
inline constexpr const common::trait_t<less_t, T, U> less{};

template <typename T, typename U>
inline constexpr const common::trait_t<greater_equal_t, T, U> greater_equal{};

template <typename T, typename U>
inline constexpr const common::trait_t<less_equal_t, T, U> less_equal{};

template <typename T, typename U>
inline constexpr const common::trait_t<logical_and_t, T, U> logical_and{};

template <typename T, typename U>
inline constexpr const common::trait_t<logical_or_t, T, U> logical_or{};

template <typename T>
inline constexpr const common::trait_t<logical_not_t, T> logical_not{};

template <typename T, typename U>
inline constexpr const common::trait_t<bit_and_t, T, U> bit_and{};

template <typename T, typename U>
inline constexpr const common::trait_t<bit_or_t, T, U> bit_or{};

template <typename T, typename U>
inline constexpr const common::trait_t<bit_xor_t, T, U> bit_xor{};

template <typename T>
inline constexpr const common::trait_t<bit_not_t, T> bit_not{};

} // namespace traits

}} // namespace blackmagic::integral::utility
